#include <vsg/all.h>
#include <vsgXchange/all.h>

#include <iostream>
#include <cxxabi.h>
#include <memory>
#include <typeinfo>
#include <sstream>
#include <tuple>
#include <cmath>

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

vsg::ref_ptr<vsg::MatrixTransform> makeStovePipe(vsg::ref_ptr<vsg::Builder> builder, const vsg::vec4& clr)
{
    vsg::GeometryInfo geomInfo;
    vsg::StateInfo stateInfo;

    float thickness = 0.05f;
    geomInfo.dx = {thickness, 0.0f, 0.0f};
    geomInfo.dy = {0.0f, thickness, 0.0f};
    geomInfo.dz = {0.0f, 0.0f, 1.0f};
    geomInfo.color = clr;
    auto z_cylinder = builder->createCylinder(geomInfo, stateInfo);
    geomInfo.dx = {.25f, 0.0f, 0.0f};
    geomInfo.dy = {0.0f, .25f, 0.0f};
    geomInfo.dz = {0.0f, 0.0f, .25f};
    geomInfo.transform = vsg::translate(0.0f, 0.0f, 0.5f);
    auto z_cone = builder->createCone(geomInfo, stateInfo);
    auto stove_pipe = vsg::MatrixTransform::create();
    stove_pipe->addChild(z_cylinder);
    stove_pipe->addChild(z_cone);
    return stove_pipe;
}

vsg::ref_ptr<vsg::MatrixTransform> makeAxes(vsg::ref_ptr<vsg::Builder> builder)
{
    float scale = 200.0f;
    auto zStovePipe = makeStovePipe(builder, vsg::vec4{0.0f, 0.0f, 1.0f, 1.0f});
    zStovePipe->matrix = vsg::scale(scale, scale, scale);

    auto xStovePipe = makeStovePipe(builder, vsg::vec4{1.0f, 0.0f, 0.0f, 1.0f});
    xStovePipe->matrix = vsg::rotate(vsg::radians(90.0f), 0.0f, 1.0f, 0.0f)
        * vsg::scale(scale, scale, scale);

    auto yStovePipe = makeStovePipe(builder, vsg::vec4{0.0f, 1.0f, 0.0f, 1.0f});
    yStovePipe->matrix = vsg::rotate(vsg::radians(90.0f), -1.0f, 0.0f, 0.0f)
        * vsg::scale(scale, scale, scale);

    auto axes = vsg::MatrixTransform::create();
    axes->addChild(zStovePipe);
    axes->addChild(xStovePipe);
    axes->addChild(yStovePipe);
    return axes;
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

class ShipObj
{
    public:
    vsg::ref_ptr<vsg::Node> objNode;
    vsg::vec3 objPosition;
    vsg::ref_ptr<vsg::MatrixTransform> objAlignWithX;
    vsg::ref_ptr<vsg::MatrixTransform> objTransform;
    vsg::vec3 thisTranslation;
    vsg::vec3 lastTranslation;
    double thisTime;
    double lastTime;
    std::function<vsg::vec3(double)> pathFunc = [](double t){return vsg::vec3((float)(sin(t/10)*2000), (float)(cos(t/10)*2000), 33.0f);};

    ShipObj(class vsg::ref_ptr<vsg::Group> scene, vsg::ref_ptr<vsg::Builder> builder)
    {
        objNode = loadObject("../models/12219_boat_v2_L2.obj");
        // objNode = loadObject("../models/ww 1 for ele.obj");
        // objNode = makeAxes(builder);
        objAlignWithX = vsg::MatrixTransform::create();
        objAlignWithX->addChild(objNode);
        objTransform = vsg::MatrixTransform::create();
        objTransform->addChild(objAlignWithX);
        lastTime = 0;
        lastTranslation = pathFunc(0);
        objAlignWithX->matrix = vsg::rotate(vsg::radians(270.0f), 1.0f, 0.0f, 0.0f)
            * vsg::rotate(vsg::radians(180.0f), 0.0f, 1.0f, 0.0f);
        objTransform->matrix = vsg::translate(lastTranslation)
            * vsg::scale(vsg::vec3(.2f, .2f, .2f));
        scene->addChild(objTransform);
    }

    vsg::dbox fetchObjBounds()
    {
        return vsg::visit<vsg::ComputeBounds>(objTransform).bounds;
    }

    vsg::vec3 fetchObjPosition()
    {
        auto bounds = fetchObjBounds();
        objPosition = (bounds.min + bounds.max) * 0.5;
        return objPosition;
    }

    void updateTransform(double _thisTime)
    {
        thisTime = _thisTime;
        thisTranslation = pathFunc(thisTime);
        objTransform->matrix = vsg::translate(thisTranslation)
            * rotateFromTranslate()
            * vsg::scale(vsg::vec3(0.2f, 0.2f, 0.2f));
    }

    private:
    vsg::mat4 rotateFromTranslate()
    {
        cout << "#############SHIP OBJECT#############" << endl;
        vsg::vec3 dx = thisTranslation - lastTranslation;
        cout << "transx: " << thisTranslation.x;
        cout << " transy: " << thisTranslation.y;
        cout << " transz: " << thisTranslation.z << endl;

        double dt = thisTime - lastTime;
        dx *= 1/(dt); 
        float theta = acos(dx.x/vsg::length(dx));
        dx = vsg::normalize(dx);

        lastTranslation = thisTranslation;
        lastTime = thisTime;

        auto cross = vsg::cross(vsg::vec3(1.0f, 0.0f, 0.0f), dx);
        cross = vsg::normalize(cross);
        cout << "dx: " << dx.x;
        cout << " dy: " << dx.y;
        cout << " dz: " << dx.z << endl;
        cout << "Cross x: " << cross.x;
        cout << " Cross y: " << cross.y;
        cout << " Cross z: " << cross.z << endl;
        cout << "Ship theta: " << vsg::degrees(theta) << endl;
        return vsg::rotate(theta, cross);
    }
};

class PlaneObj
{
    public:
    vsg::ref_ptr<vsg::Node> objNode;
    vsg::vec3 objPosition;
    vsg::ref_ptr<vsg::MatrixTransform> objAlignWithX;
    vsg::ref_ptr<vsg::MatrixTransform> objTransform;
    vsg::vec3 thisTranslation;
    vsg::vec3 lastTranslation;
    double thisTime;
    double lastTime;
    std::function<vsg::vec3(double)> pathFunc = [](double t){return vsg::vec3((float)(-sin(t/10)*5000), (float)(cos(t/10)*5000), 2000.0f);};

    PlaneObj(class vsg::ref_ptr<vsg::Group> scene)
    {
        objNode = loadObject("../models/ww 1 for ele.obj");
        objAlignWithX = vsg::MatrixTransform::create();
        objAlignWithX->addChild(objNode);
        objTransform = vsg::MatrixTransform::create();
        objTransform->addChild(objAlignWithX);
        lastTime = 0;
        lastTranslation = pathFunc(0);
        objAlignWithX->matrix = vsg::rotate(vsg::radians(90.0f), 0.0f, 0.0f, 1.0f);
        objTransform->matrix = vsg::translate(lastTranslation);
        scene->addChild(objTransform);
    }

    vsg::dbox fetchObjBounds()
    {
        return vsg::visit<vsg::ComputeBounds>(objTransform).bounds;
    }

    vsg::vec3 fetchObjPosition()
    {
        auto bounds = fetchObjBounds();
        objPosition = (bounds.min + bounds.max) * 0.5;
        return objPosition;
    }

    void updateTransform(double _thisTime)
    {
        thisTime = _thisTime;
        thisTranslation = pathFunc(thisTime);
        objTransform->matrix = vsg::translate(thisTranslation)
            * rotateFromTranslate();
    }

    private:
    vsg::mat4 rotateFromTranslate()
    {
        cout << "#############PLANE OBJECT#############" << endl;
        vsg::vec3 dx = thisTranslation - lastTranslation;
        cout << "transx: " << thisTranslation.x;
        cout << " transy: " << thisTranslation.y;
        cout << " transz: " << thisTranslation.z << endl;

        double dt = thisTime - lastTime;
        dx *= 1/(dt); 
        float theta = acos(dx.x/vsg::length(dx));
        dx = vsg::normalize(dx);
        lastTranslation = thisTranslation;
        lastTime = thisTime;

        auto cross = vsg::cross(vsg::vec3(1.0f, 0.0f, 0.0f), dx);
        cross = vsg::normalize(cross);
        cout << "dx: " << dx.x;
        cout << " dy: " << dx.y;
        cout << " dz: " << dx.z << endl;
        cout << "Cross x: " << cross.x;
        cout << " Cross y: " << cross.y;
        cout << " Cross z: " << cross.z << endl;
        cout << "Plane theta: " << vsg::degrees(theta) << endl;

        return vsg::rotate(theta, cross);
    }
};

std::tuple<vsg::ref_ptr<vsg::Node>, ShipObj, PlaneObj> createShipScene(vsg::ref_ptr<vsg::Options> options)
{
    auto builder = vsg::Builder::create();
    builder->options = options;

    auto scene = vsg::Group::create();

    vsg::GeometryInfo geomInfo;
    vsg::StateInfo stateInfo;

    // Skybox
    auto sky = loadObject("../models/skybox.vsgt");
    scene->addChild(sky);

    // Ship
    ShipObj ship(scene, builder);

    // Plane
    PlaneObj plane(scene);

    //Axes
    auto axes = makeAxes(builder);
    scene->addChild(axes);
    cout << "axes generated" << endl;

    // Ocean
    geomInfo.position.set(0.0f, 0.0f, 0.0f);
    geomInfo.dx.set(20000.0f, 0.0f, 0.0f);
    geomInfo.dy.set(0.0f, 20000.0f, 0.0f);
    geomInfo.color.set(0.0f, 0.0f, 1.0f, 0.0f);

    scene->addChild(builder->createQuad(geomInfo, stateInfo));

    return std::make_tuple(scene, ship, plane);
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

    // set up defaults and read command line arguments to override them
    vsg::CommandLine arguments(&argc, argv);

    auto windowTraits = vsg::WindowTraits::create();
    windowTraits->windowTitle = "Multiple Windows - first window";
    windowTraits->debugLayer = arguments.read({"--debug", "-d"});
    windowTraits->apiDumpLayer = arguments.read({"--api", "-a"});
    if (arguments.read({"--window", "-w"}, windowTraits->width, windowTraits->height)) { windowTraits->fullscreen = false; }

    // auto windowTraits2 = vsg::WindowTraits::create();
    // windowTraits2->windowTitle = "Multiple Windows - second window";
    // windowTraits2->debugLayer = windowTraits->debugLayer;
    // windowTraits2->apiDumpLayer = windowTraits->apiDumpLayer;
    // windowTraits2->width = 640;
    // windowTraits2->height = 480;
    // if (arguments.read({"--window2", "-w2"}, windowTraits2->width, windowTraits2->height)) { windowTraits2->fullscreen = false; }

    if (arguments.errors()) return arguments.writeErrorMessages(std::cerr);

    bool multiThreading = arguments.read("--mt");
    bool separateDevices = arguments.read({"--no-shared-window", "-n"});
    // bool useStagingBuffer = arguments.read({"--staging-buffer", "-s"});

    auto outputFilename = arguments.value<vsg::Path>("", "-o");

    if (separateDevices && VSG_MAX_DEVICES < 2)
    {
        std::cout << "VulkanSceneGraph built with VSG_MAX_DEVICES = " << VSG_MAX_DEVICES << ", so using two windows, with a vsg::Device per vsg::Window is not supported." << std::endl;
        return 1;
    }
    
    auto tup = createShipScene(options);
    auto scene = std::get<0>(tup);
    auto ship = std::get<1>(tup);
    auto plane = std::get<2>(tup);

    auto group = vsg::Group::create();
    group->addChild(scene);

    // Lights
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

    // compute the bounds of the scene graph to help position camera
    auto bounds = vsg::visit<vsg::ComputeBounds>(scene).bounds;
    vsg::dvec3 centre = (bounds.min + bounds.max) * 0.5;
    double radius = vsg::length(bounds.max - bounds.min) * 0.6;

    auto sBounds = vsg::visit<vsg::ComputeBounds>(ship.objTransform).bounds;
    vsg::dvec3 sCentre = (sBounds.min + sBounds.max) * 0.5;
    
    auto pBounds = vsg::visit<vsg::ComputeBounds>(plane.objTransform).bounds;
    vsg::dvec3 pCentre = (pBounds.min + pBounds.max) * 0.5;
    double pRadius = vsg::length(pBounds.max - pBounds.min) * 0.05;

    // create the viewer and assign window(s) to it
    auto viewer = vsg::Viewer::create();

    auto window = vsg::Window::create(windowTraits);
    // if (!window)
    // {
    //     std::cout << "Could not create window." << std::endl;
    //     return 1;
    // }

    // if (!separateDevices)
    // {
    //     windowTraits2->device = window->getOrCreateDevice(); // share the same vsg::Instance/vsg::Device as window1
    //     std::cout << "Sharing vsg::Instance and vsg::Device between windows." << std::endl;
    // }
    // else
    // {
    //     std::cout << "Each window to use its own vsg::Instance and vsg::Device." << std::endl;
    // }
    // auto pWindow = vsg::Window::create(windowTraits2);
    // if (!pWindow)
    // {
    //     std::cout << "Could not create second window." << std::endl;
    //     return 1;
    // }

    // Add window
    viewer->addWindow(window);
    // viewer->addWindow(pWindow);

    // Create camera and view
    vsg::ref_ptr<vsg::LookAt> lookAt;
    vsg::ref_ptr<vsg::LookAt> pLookAt;

    // set up the camera
    lookAt = vsg::LookAt::create(pCentre + vsg::dvec3(0.0, -pRadius * 3.5, 0.0), pCentre, vsg::dvec3(0.0, 0.0, 1.0));
    pLookAt = vsg::LookAt::create(pCentre, sCentre, vsg::dvec3(0.0, 0.0, 1.0));

    double nearFarRatio = 0.001;
    auto perspective = vsg::Perspective::create(30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio * radius, radius * 10.0);

    auto camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));
    // auto pCamera = vsg::Camera::create(perspective, pLookAt, vsg::ViewportState::create(pWindow->extent2D()));

    // add the camera and scene graph to View
    auto view = vsg::View::create();
    auto pView = vsg::View::create();

    view->camera = camera;
    // pView->camera = pCamera;

    view->addChild(scene);
    // pView->addChild(scene);
    
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
    // auto pRenderGraph = vsg::RenderGraph::create(pWindow, pView);

    auto commandGraph = vsg::CommandGraph::create(window);
    commandGraph->addChild(renderGraph);

    // auto pCommandGraph = vsg::CommandGraph::create(pWindow);
    // pCommandGraph->addChild(pRenderGraph);

    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});
    // viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph, pCommandGraph});

    if (multiThreading)
    {
        viewer->setupThreading();
    }

    viewer->compile();

    auto startTime = vsg::clock::now();
    double numFramesCompleted = 0.0;

    
    // rendering main loop
    while (viewer->advanceToNextFrame())
    {
        auto t = std::chrono::duration<double, std::chrono::seconds::period>(vsg::clock::now() - startTime).count();
        ship.updateTransform(t);
        plane.updateTransform(t);
        
        sBounds = vsg::visit<vsg::ComputeBounds>(ship.objTransform).bounds;
        sCentre = (sBounds.min + sBounds.max) * 0.5;

        pBounds = vsg::visit<vsg::ComputeBounds>(plane.objTransform).bounds;
        pCentre = (pBounds.min + pBounds.max) * 0.5;

        lookAt->center = pCentre;
        lookAt->up = vsg::dvec3(0.0, 0.0, 1.0);

        pLookAt->eye =  pCentre;
        pLookAt->center =  sCentre;
        pLookAt->up = vsg::dvec3(0.0, 0.0, 1.0);

        if(*planeCamera == false)
        {
            camera->viewMatrix = lookAt;
        }
        else
        {
            camera->viewMatrix = pLookAt;
        }
        
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
