#pragma once
#include <vsg/all.h>
#include <iostream>
#include <cmath>

#include "pData.hpp"

class PModel
{
public:
    vsg::ref_ptr<vsg::MatrixTransform> pendulum;

    PModel(vsg::ref_ptr<vsg::Builder> _builder);
    void updatePendulum(PData pData);

private:
    vsg::ref_ptr<vsg::Builder> builder;
    vsg::ref_ptr<vsg::MatrixTransform> link1;
    vsg::vec3 joint1;
    vsg::ref_ptr<vsg::MatrixTransform> link2;
    
    vsg::ref_ptr<vsg::MatrixTransform> createLink();
};

class AModel
{
public:
    vsg::ref_ptr<vsg::MatrixTransform> axes;

    AModel(vsg::ref_ptr<vsg::Builder> _builder);
private:
    vsg::ref_ptr<vsg::Builder> builder;

    vsg::ref_ptr<vsg::MatrixTransform> makeStovePipe(vsg::ref_ptr<vsg::Builder> builder, const vsg::vec4& clr);

};