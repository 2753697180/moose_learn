//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ADDiffusion.h"

class ADHeatConduction : public ADDiffusion
{
public:
  static InputParameters validParams(); //定了义了一个静态函数，返回类型是InputParameters
  //静态函数是类的函数，可以通过类名直接调用，不需要创建类的对象

  ADHeatConduction(const InputParameters & parameters);//定义了一个构造函数，用于初始化

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  const ADMaterialProperty<Real> & _thermal_conductivity;//引用材料属性，定义在材料模块，后续材料值通过输入文件传递
};
//public部分是参数，protected部分是函数和变量 
//public是公用的，类内类外都可以访问到，protected是受保护的，只有类内和子类可以访问，private是私有的，只有类内可以访问
// 其中的函数是重写父类的虚函数
// 变量是计算所需变量，
