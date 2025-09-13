//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "ADHeatConduction.h"

registerMooseObject("HeatTransferApp", ADHeatConduction);

InputParameters// 返回类型 InputParameters::InputParameters
ADHeatConduction::validParams()
{
  InputParameters params = ADDiffusion::validParams();
  params.addParam<MaterialPropertyName>("thermal_conductivity",
                                        "thermal_conductivity",
                                        "the name of the thermal conductivity material property");//添加热导率参数到材料属性中
  params.set<bool>("use_displaced_mesh") = true;//设置使用位移网格
  return params;
}

ADHeatConduction::ADHeatConduction(const InputParameters & parameters)
  : ADDiffusion(parameters),// 初始化，采用父类的构造函数
    _thermal_conductivity(getADMaterialProperty<Real>("thermal_conductivity"))// 初始化材料属性
{
}

ADRealVectorValue //返回类型，
ADHeatConduction::precomputeQpResidual() //在头文件ADHeatConduction.h中继承重载的虚函数
{
  return _thermal_conductivity[_qp] * ADDiffusion::precomputeQpResidual();
  //调用父类的函数，并乘以热导率 换算成数学语言就是，k*（grad_uj*phj）*(grad_phi)
  //由于这里是AD类型，直接完成grad_phi的计算，在moose中就显示为k*grad_u

}
