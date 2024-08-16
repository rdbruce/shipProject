#include <vsg/all.h>
#include <vsgXchange/all.h>


#include <iostream>
#include <cxxabi.h>
#include <memory>
#include <typeinfo>
#include <sstream>
#include <tuple>

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

ostream& operator<<(ostream& os, const vsg::GeometryInfo& gi)
{
    stringstream ss;
    ss << "[ position=" << gi.position << " transform=" << gi.transform << " color=" << gi.color << " ]";
    return os << ss.str();
}

vsg::ref_ptr<vsg::Node> createTextureQuad(vsg::ref_ptr<vsg::Data> sourceData, vsg::ref_ptr<vsg::Options> options)
{
    auto builder = vsg::Builder::create();
    builder->options = options;

    vsg::StateInfo state;
    state.image = sourceData;
    state.lighting = false;

    vsg::GeometryInfo geom;
    geom.dy.set(0.0f, 0.0f, 1.0f);
    geom.dz.set(0.0f, -1.0f, 0.0f);

    return builder->createQuad(geom, state);
}

vsg::ref_ptr<vsg::Node> loadObject(string filepath)
{
    vsg::Path vsgFilePath = filepath;
    vsg::ref_ptr<vsg::Object> object;
    auto options = vsg::Options::create();
    
    // add vsgXchange's support for reading and writing 3rd party file formats
    options->add(vsgXchange::all::create());

    if(vsgFilePath.find(".vsg") != std::string::npos)
    {
        object = vsg::read(vsgFilePath, options);
        std::cout << "vsg" << std::endl;
    }
    else
    {
        object = vsg::read_cast<vsg::Node>(vsgFilePath, options);
        std::cout << "novsg" << std::endl;
    }

    if (vsg::ref_ptr<vsg::Node> node = object.cast<vsg::Node>())
    {
        return node;
    }
    else if (auto data = object.cast<vsg::Data>())
    {
        if (vsg::ref_ptr<vsg::Node> textureGeometry = createTextureQuad(data, options))
        {
            return node;
        }
    }
    else if (object)
    {
        std::cout << "Unable to view object of type " << object->className() << std::endl;
    }
    else
    {
        std::cout << "Unable to load file " << vsgFilePath << std::endl;
    }
    vsg::ref_ptr<vsg::Node> node;
    return node;
}

std::tuple<vsg::ref_ptr<vsg::Node>, vsg::ref_ptr<vsg::MatrixTransform>> createShipScene(vsg::ref_ptr<vsg::Options> options)
{
    auto builder = vsg::Builder::create();
    builder->options = options;

    auto scene = vsg::Group::create();

    vsg::GeometryInfo geomInfo;
    vsg::StateInfo stateInfo;

    auto sky = loadObject("../models/skybox.vsgt");
    scene->addChild(sky);

    auto ship = loadObject("../models/12219_boat_v2_L2.obj");
    vsg::ref_ptr<vsg::MatrixTransform> shipLocation = vsg::MatrixTransform::create();
    shipLocation->matrix = vsg::rotate(vsg::radians(270.0f), 1.0f, 0.0f, 0.0f)
        * vsg::translate(vsg::vec3(0.0f, 33.0f, 0.0f))
        * vsg::scale(vsg::vec3(.2f, .2f, .2f));
    shipLocation->addChild(ship);
    scene->addChild(shipLocation);

    auto bounds = vsg::visit<vsg::ComputeBounds>(scene).bounds;
    double diameter = vsg::length(bounds.max - bounds.min);
    geomInfo.position.set(0.0f, 0.0f, 0.0f);
    geomInfo.dx.set(2000.0f, 0.0f, 0.0f);
    geomInfo.dy.set(0.0f, 2000.0f, 0.0f);
    geomInfo.color.set(0.0f, 0.0f, 1.0f, 0.0f);

    scene->addChild(builder->createQuad(geomInfo, stateInfo));

    return std::make_tuple(scene, shipLocation);
}

int main(int argc, char** argv)
{
    auto options = vsg::Options::create();
    options->paths = vsg::getEnvPaths("VSG_FILE_PATH");
    options->sharedObjects = vsg::SharedObjects::create();

#ifdef vsgXchange_all
    // add vsgXchange's support for reading and writing 3rd party file formats
    options->add(vsgXchange::all::create());
#endif

    auto windowTraits = vsg::WindowTraits::create();
    windowTraits->windowTitle = "vsglights";

    // set up defaults and read command line arguments to override them
    vsg::CommandLine arguments(&argc, argv);
    windowTraits->debugLayer = arguments.read({"--debug", "-d"});
    windowTraits->apiDumpLayer = arguments.read({"--api", "-a"});

    arguments.read("--screen", windowTraits->screenNum);
    arguments.read("--display", windowTraits->display);
    auto numFrames = arguments.value(-1, "-f");
    if (arguments.read({"--fullscreen", "--fs"})) windowTraits->fullscreen = true;
    if (arguments.read({"--window", "-w"}, windowTraits->width, windowTraits->height)) { windowTraits->fullscreen = false; }
    if (arguments.read("--IMMEDIATE")) windowTraits->swapchainPreferences.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
    if (arguments.read({"-t", "--test"}))
    {
        windowTraits->swapchainPreferences.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
        windowTraits->fullscreen = true;
    }
    if (arguments.read("--st"))
    {
        windowTraits->swapchainPreferences.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
        windowTraits->width = 192, windowTraits->height = 108;
        windowTraits->decoration = false;
    }

    // bool useStagingBuffer = arguments.read({"--staging-buffer", "-s"});

    auto outputFilename = arguments.value<vsg::Path>("", "-o");

    bool add_ambient = false;
    bool add_directional = true;
    bool add_point = false;
    bool add_spotlight = false;
    bool add_headlight = arguments.read("--headlight");
    if (add_headlight || arguments.read({"--no-lights", "-n"}))
    {
        add_ambient = false;
        add_directional = false;
        add_point = false;
        add_spotlight = false;
    }


    auto tup = createShipScene(options);
    auto scene = std::get<0>(tup);
    auto shipLocation = std::get<1>(tup);

    // compute the bounds of the scene graph to help position camera
    auto bounds = vsg::visit<vsg::ComputeBounds>(scene).bounds;

    auto span = vsg::length(bounds.max - bounds.min);
    auto group = vsg::Group::create();
    group->addChild(scene);

    auto directionalLight = vsg::DirectionalLight::create();
    directionalLight->name = "directional";
    directionalLight->color.set(1.0f, 1.0f, 1.0f);
    directionalLight->intensity = 0.85f;
    directionalLight->direction.set(0.0f, -1.0f, -1.0f);
    group->addChild(directionalLight);

    scene = group;

    // write out scene if required
    if (outputFilename)
    {
        vsg::write(scene, outputFilename, options);
        return 0;
    }

    // create the viewer and assign window(s) to it
    auto viewer = vsg::Viewer::create();

    auto window = vsg::Window::create(windowTraits);
    if (!window)
    {
        std::cout << "Could not create window." << std::endl;
        return 1;
    }

    viewer->addWindow(window);

    vsg::ref_ptr<vsg::LookAt> lookAt;

    vsg::dvec3 centre = (bounds.min + bounds.max) * 0.5;
    double radius = vsg::length(bounds.max - bounds.min) * 0.6;

    // set up the camera
    lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, radius * 0.5, radius * 3.5), centre, vsg::dvec3(0.0, 0.0, 1.0));

    double nearFarRatio = 0.001;
    auto perspective = vsg::Perspective::create(30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio * radius, radius * 10.0);

    auto camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));

    // add the camera and scene graph to View
    auto view = vsg::View::create();
    view->camera = camera;
    view->addChild(scene);

    // add close handler to respond to the close window button and to pressing escape
    viewer->addEventHandler(vsg::CloseHandler::create(viewer));
    viewer->addEventHandler(vsg::Trackball::create(camera));

    auto renderGraph = vsg::RenderGraph::create(window, view);
    auto commandGraph = vsg::CommandGraph::create(window, renderGraph);
    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

    viewer->compile();

    auto startTime = vsg::clock::now();
    double numFramesCompleted = 0.0;

    // rendering main loop
    while (viewer->advanceToNextFrame() && (numFrames < 0 || (numFrames--) > 0))
    {
        auto t = std::chrono::duration<double, std::chrono::seconds::period>(vsg::clock::now() - startTime).count();
        shipLocation->matrix = vsg::rotate(vsg::radians(270.0f), 1.0f, 0.0f, 0.0f)
        * vsg::translate(vsg::vec3(0.0f, 33.0f, 0.0f))
        * vsg::scale(vsg::vec3(.2f, .2f, .2f))
        * vsg::rotate((float)(-M_PI*t/10), 0.0f, 1.0f, 0.0f)
        * vsg::translate((float)(-sin(t/10)*2000), 0.0f, (float)(cos(t/10)*2000));
        // shipLocation->matrix = vsg::translate(vsg::vec3(0.0f, sin(t), 0.0f))
        //     * vsg::scale(vsg::vec3(.2f, .2f, .2f)) 
        //     * vsg::rotate(vsg::radians(45.0f * (float)sin(t)), 0.0f, 1.0f, 0.0f);

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
