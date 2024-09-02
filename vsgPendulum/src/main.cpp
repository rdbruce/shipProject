#include <vsg/all.h>

#include <iostream>
#include <cxxabi.h>
#include <memory>
#include <typeinfo>
#include <sstream>
#include <tuple>
#include <cmath>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <functional>
#include <vector>
#include <unistd.h>

#include "builderModels.hpp"
#include "pMath.hpp"

//Generic thread wrapper
class Simulator {
public:
    using Callback = std::function<void ()>;
private:
    Callback callback;
    bool die;
    std::thread tid;
    std::string name;
public:
	//Construct std function from provided callable
    Simulator(Callback _callback) : callback(_callback), die(false)
    {
		//Create thread
        tid = std::thread([this]() { this->worker(); });
    }

    ~Simulator()
    {
        {
            die = true;
        }
        tid.join();
    }

	//Generic run loop that pMath exists in
    void worker()
    {
        using namespace std;
        for (;;) {
            callback();
            if (die) return;
        }
    }
};

//Generic SafeSharedPtr
template <typename T>
class SafeSharedPtr {
    std::mutex  mtx;
    std::shared_ptr<T>  ptr;
public:
    SafeSharedPtr() : ptr(nullptr) {}

    void store(std::shared_ptr<T> arg)
    {
        std::unique_lock<std::mutex> lock(mtx);
        ptr = arg;
    }

    std::shared_ptr<T> load()
    {
        std::unique_lock<std::mutex> lock(mtx);
        return ptr;
    }
};

template <typename T>
std::string demangle(T&&) {
    auto name = typeid(T).name();
    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}

using namespace std;

class InputHandler : public vsg::Inherit<vsg::Visitor, InputHandler>
{
public:
    InputHandler()
    {
        b = false;
    }

    void apply(vsg::KeyPressEvent& keyPress) override
    {
        if (keyPress.keyBase == vsg::KEY_Space);
        {
            b = !b;
        }
    }

    operator bool() const
    {
        return b;
    }
private:
    bool b;
};

int main(int argc, char** argv)
{
    auto options = vsg::Options::create();
    options->paths = vsg::getEnvPaths("VSG_FILE_PATH");
    options->sharedObjects = vsg::SharedObjects::create();

    // set up defaults and read command line arguments to override them
    vsg::CommandLine arguments(&argc, argv);

    auto windowTraits = vsg::WindowTraits::create();
    windowTraits->windowTitle = "Multiple Windows - first window";
    windowTraits->debugLayer = arguments.read({"--debug", "-d"});
    windowTraits->apiDumpLayer = arguments.read({"--api", "-a"});
    if (arguments.read({"--window", "-w"}, windowTraits->width, windowTraits->height)) { windowTraits->fullscreen = false; }

    if (arguments.errors()) return arguments.writeErrorMessages(std::cerr);

    bool multiThreading = arguments.read("--mt");
    bool separateDevices = arguments.read({"--no-shared-window", "-n"});
    // bool useStagingBuffer = arguments.read({"--staging-buffer", "-s"});

    if (separateDevices && VSG_MAX_DEVICES < 2)
    {
        std::cout << "VulkanSceneGraph built with VSG_MAX_DEVICES = " << VSG_MAX_DEVICES << ", so using two windows, with a vsg::Device per vsg::Window is not supported." << std::endl;
        return 1;
    }
    
    // CREATE SCENE
    auto builder = vsg::Builder::create();
    builder->options = options;

    auto group = vsg::Group::create();

    // Axes
    AModel aModel(builder);
    auto axes = aModel.axes;
    group->addChild(axes);

    // Pendulum
    PModel pModel(builder);
    auto pendulum = pModel.pendulum;
    group->addChild(pendulum);

    // Lights
    auto directionalLight = vsg::DirectionalLight::create();
    directionalLight->name = "directional";
    directionalLight->color.set(1.0f, 1.0f, 1.0f);
    directionalLight->intensity = 0.85f;
    directionalLight->direction.set(-1.0f, 0.0f, -1.0f);
    group->addChild(directionalLight);

    auto scene = vsg::Node::create();
    scene = group;

    // compute the bounds of the scene graph to help position camera
    auto bounds = vsg::visit<vsg::ComputeBounds>(scene).bounds;
    vsg::dvec3 centre = (bounds.min + bounds.max) * 0.5;
    double radius = vsg::length(bounds.max - bounds.min) * 0.6;

    // vsg::dvec3 centre(0.0f, 0.0f, 0.0f);
    // double radius = 200.0;

    // create the viewer and assign window(s) to it
    auto viewer = vsg::Viewer::create();

    auto window = vsg::Window::create(windowTraits);

    // Add window
    viewer->addWindow(window);
    // viewer->addWindow(pWindow);

    // Create camera and view
    vsg::ref_ptr<vsg::LookAt> lookAt;

    // set up the camera
    lookAt = vsg::LookAt::create(vsg::dvec3(radius * 3.5, 0.0, 0.0), vsg::dvec3(0.0, 0.0, 0.0), vsg::dvec3(0.0, 0.0, 1.0));

    double nearFarRatio = 0.001;
    auto perspective = vsg::Perspective::create(30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio * radius, radius * 10.0);

    auto camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));
    // auto pCamera = vsg::Camera::create(perspective, pLookAt, vsg::ViewportState::create(pWindow->extent2D()));

    // add the camera and scene graph to View
    auto view = vsg::View::create();

    view->camera = camera;

    view->addChild(scene);
    
    // Add close handler to respond to the close window button and to pressing escape
    viewer->addEventHandler(vsg::CloseHandler::create(viewer));

    // Add trackball for controllable window
    auto main_trackball = vsg::Trackball::create(camera);
    main_trackball->addWindow(window);
    viewer->addEventHandler(main_trackball);

    // assign Input handler
    auto planeCamera = InputHandler::create();
    viewer->addEventHandler(planeCamera);

    auto renderGraph = vsg::RenderGraph::create(window, view);

    auto commandGraph = vsg::CommandGraph::create(window);
    commandGraph->addChild(renderGraph);

    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

    if (multiThreading)
    {
        viewer->setupThreading();
    }

    viewer->compile();

    auto startTime = vsg::clock::now();
    double numFramesCompleted = 0.0;

    //Initialize pendulum position structure pointer
    SafeSharedPtr<PData> latch;
	//Initialize mathematical model 
	pMath ourPm(3.1415, 3.1415); //Input thetas
	//Call generic thread creator and initialize with our callable
    Simulator s([&]() { auto ptr = ourPm.simulate(); latch.store(ptr); });

    // rendering main loop
    while (viewer->advanceToNextFrame())
    {
        auto t = std::chrono::duration<double, std::chrono::seconds::period>(vsg::clock::now() - startTime).count();

        auto ptr = latch.load();
        pModel.updatePendulum(*ptr);
        
        // pass any events into EventHandlers assigned to the Viewer
        viewer->handleEvents();
        viewer->update();
        viewer->recordAndSubmit();
        viewer->present();

        numFramesCompleted += 1.0;
    }

    auto duration = std::chrono::duration<double, std::chrono::seconds::period>(vsg::clock::now() - startTime).count();
    if (numFramesCompleted > 0.0)
    {
        std::cout << "Average frame rate = " << (numFramesCompleted / duration) << std::endl;
    }

    return 0;
}
