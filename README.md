mooselearn
//moose中涉及的知识主要为FEM，C++，以及git，其中，建议学习一下git的基础命令，方便利用GitHub托管代码，与克隆代码。
安装好moose后，创建自己的app，随意命名即可，如cat，然后将此库克隆在cat下即可，通过moose创建的app是附带有git的。
一个完整的有限元计算流程，涉及到数学方程建模，有限元方式空间离散与时间离散，单元积分与组装方程
对于moose对象本身而言，moose框架设立思想是每个类及其子类完成一部分工作，最基础的类是计算框架（如对单元积分，方程组装，编码雅可比矩阵，求解方程等等）
这些计算框架内的基本类对象是隐藏的，刚开始了解即可，不必过于深究。（我们要使用的类大概是Kernel类：方程离散项的表述，BC类：边界条件的表述）
我们要利用的是类的接口，分为内部接口与外部接口（非编程概念，自己定的）
外部接口：就是输入文件，在输入文件中按照方程本身要求解的问题的数学描写，离散后的方程项，在不同的模块中选取合适的类，按照类的使用说明与要解决的问题编辑输入文件即可（所有类的源文件说明在此查看，https://mooseframework.inl.gov/source/index.html）
（建议是按模块查看，比如传热，流体等等，模块链接：https://mooseframework.inl.gov/modules/index.html）
以下是一些补充说明
关于Kernel类：
此文本说明选取对象为稳态导热方程（热力学）也是扩散方程，或者说是拉普拉斯算子，都是一样的数学的形式，
                            方程形式为div(grad_u)=q（左端是拉普拉斯算子，右端为源项）
方程中含有散度项，这也是离散的基础，具体的离散过程参考 https://mooseframework.inl.gov/syntax/Kernels/
更详细的离散过程，可以参考，PDEppt/comsol的博客（https://cn.comsol.com/multiphysics/finite-element-method）
数学方程离散后的每一项在moose中都叫做kernel，
moose中离散后的方程的统一形式为，R（x）=Ax-b；R（x）叫做残差，数值解的目的就是使得R(x)趋近于0，
R(x)的方程组装，也就是离散方程项的组装，在moose中叫做kernel,
Kernel在moose中有ADKernel，Kernel之分，区别在于自动微分，这个指的是自动与手动编码雅可比矩阵的问题
所以有些代码里面是含有computeQpJacobian()这个函数，就是为了完成手动编码雅可比矩阵，建议在刚开始使用时，使用ADKernel类
（关于AD的说明，详见https://mooseframework.inl.gov/automatic_differentiation/index.html）
注意moose中的ADkernel有三种类型ADKernel，ADKernelValue，ADKernelGrad，
三者的区别主要针对于test function而言，
当离散项中含有test function或 grad_test function时， ADKernel需明确组装，组装逻辑是_test[_i][_qp]或_grad_test[i]_[qp]    
当离散项中仅含有test function时，可采用ADKernelValue，此时，moose框架会自动完成_test[_i][_qp]的组装，不需要显式声明，
同理，当离散项中仅含有grad_test function时，可采用ADKernelGrad，moose框架会自动完成_grad_test[i]_[qp]的组装，不需要显式声明，
对应的计算函数分别是 computeQpResidual precomputeQpResidual precomputeQpResidual（三者计算逻辑是一样的，pre指的是预处理）


