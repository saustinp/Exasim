<p align="center">
<img src="Documentation/exasimlogosmall.png">
</p>

# Generating Discontinuous Galerkin Codes For Extreme Scalable Simulations
Exasim is an open-source software for generating implicit discontinuous Galerkin codes to numerically solve parametrized partial differential equations (PDEs) on different computing platforms with distributed memory.  It combines high-level languages and low-level languages to easily construct parametrized PDE models and automatically produce high-performance C++ codes. The construction of parametrized PDE models and the generation of the stand-alone C++ production code are handled by high-level languages, while the production code itself can run on various machines, from laptops to the largest supercomputers, with both CPU and Nvidia GPU processors. 

\begin{itemize}
\item \texttt{Exasim} intuitively simplifies  modeling and simulation % with an intuitive interface.
\item  generates stand-alone C++ production code and gives practitioners  freedom to modify the code and execute it as desired
\item provides implicit high-order DG solution of parametrized PDE models
\item provides full GPU functionality, meaning that all code components from discretization schemes to iterative solvers are deployed fully on GPUs
\item and is available in Julia, Python, and Matlab. 
\end{itemize}

# Dependency  

Exasim automatically generates and compiles stand-alone C++ code on the fly. To do that, Exasim requires a C++ compiler and Blas/Lapack libraries for generating serial code. An MPI library is required to compile and run parallel code. CUDA Tookit is required to run CUDA code on Nvidia GPUs. Gmesh is used for mesh generation. METIS is needed for mesh partitioning. And Paraview is used for visualization. To install these packages, please go to the directory Exasim/Installation and run install.jl in Julia, install.py in Python, or install.m in Matlab. See the documentation https://github.com/exapde/Exasim/tree/master/Documentation/Exasim0.3.pdf for more details. 

# Language Support

Exasim is available in Julia, Python, and Matlab. 

# Partial Differential Equations

Exasim produces C++ Code to solve a wide variety of parametrized partial differential equations from first-order PDEs, second-order elliptic, parabolic, hyperbolic PDEs, to higher-order PDEs.

# Applications

Many examples are provided to illustrate how to build stand-alone DG code for solving a wide variety of PDEs including Poisson equation, wave equation, heat equation, advection, convection-diffusion, elasticity, Euler equations, Navier-Stokes equations, and MHD equations. To try out any of the provided examples, please go to any folder under Exasim/Applications and run pdeapp.jl in Julia, pdeapp.py in Python, or pdeapp.m in Matlab. See https://github.com/exapde/Exasim/blob/master/Applications/ShallowWater/BickleyJet/BickleyJet.pdf for simulation results of the Bickley Jet problem.

# Publications
[1] A Matrix-Free Implicit Discontinuous Galerkin Method for Large Eddy Simulation of Transonic Buffet at High Reynolds Number on Graphics Processors. https://github.com/exapde/Exasim/tree/master/Documentation/AIAA_Journal_2020_OAT15A.pdf 
