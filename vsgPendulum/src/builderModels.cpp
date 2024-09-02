#include "builderModels.hpp"

PModel::PModel(vsg::ref_ptr<vsg::Builder> _builder) : builder(_builder)
{
    auto link1Start = createLink();
    link1Start->matrix = vsg::translate(-7.5f, 0.0f, 0.0f)
        * vsg::rotate(vsg::radians(90.0f), 0.0f, 1.0f, 0.0f);
    link1 = vsg::MatrixTransform::create();
    link1->addChild(link1Start);

    auto link2Start = createLink();
    link2Start->matrix = vsg::translate(7.5f, 0.0f, 0.0f)
        * vsg::rotate(vsg::radians(90.0f), 0.0f, 1.0f, 0.0f);
    link2 = vsg::MatrixTransform::create();
    link2->addChild(link2Start);

    link2->matrix = vsg::translate(0.0f, 0.0f, -200.0f);

    pendulum = vsg::MatrixTransform::create();
    pendulum->addChild(link1);
    pendulum->addChild(link2);

    std::cout << "PModel Generated" << std::endl;
}

vsg::ref_ptr<vsg::MatrixTransform> PModel::createLink()
{
    auto link = vsg::MatrixTransform::create();
    vsg::GeometryInfo geomInfo;
    vsg::StateInfo stateInfo;

    geomInfo.dx = {50.0f, 0.0f, 0.0f};
    geomInfo.dy = {0.0f, 50.0f, 0.0f};
    geomInfo.dz = {0.0f, 0.0f, 15.0f};
    link->addChild(builder->createCylinder(geomInfo, stateInfo));

    geomInfo.dx = {200.0f, 0.0f, 0.0f};
    geomInfo.dy = {0.0f, 50.0f, 0.0f};
    geomInfo.dz = {0.0f, 0.0f, 15.0f};
    geomInfo.transform = vsg::translate(100.0f, 0.0f, 0.0f);
    link->addChild(builder->createBox(geomInfo, stateInfo));

    geomInfo.dx = {50.0f, 0.0f, 0.0f};
    geomInfo.dy = {0.0f, 50.0f, 0.0f};
    geomInfo.dz = {0.0f, 0.0f, 15.0f};
    geomInfo.transform = vsg::translate(200.0f, 0.0f, 0.0f);
    link->addChild(builder->createCylinder(geomInfo, stateInfo));

    return link;
}

void PModel::updatePendulum(PData pData)
{
    joint1 = vsg::vec3(0.0f, 200.0f*sin(pData.t), -200.0f*cos(pData.t));
    // pt2 = { (int)(pt1.x + 200.0f*sin(pData.t2) + 0.5), (int)(pt1.y + 200.0f*cos(pData.t2) + 0.5) };

    link1->matrix = vsg::rotate(pData.t, 1.0f, 0.0f, 0.0f);
    link2->matrix = vsg::translate(joint1)
        * vsg::rotate(pData.t2, 1.0f, 0.0f, 0.0f);
}

AModel::AModel(vsg::ref_ptr<vsg::Builder> _builder) : builder(_builder)
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

    axes = vsg::MatrixTransform::create();
    axes->addChild(zStovePipe);
    axes->addChild(xStovePipe);
    axes->addChild(yStovePipe);
    std::cout << "AModel Generated" << std::endl;
}

vsg::ref_ptr<vsg::MatrixTransform> AModel::makeStovePipe(vsg::ref_ptr<vsg::Builder> builder, const vsg::vec4& clr)
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