#ifndef __PTCSOLVER
#define __PTCSOLVER

int LinearSolver(sysstruct &sys, CDiscretization& disc, CPreconditioner& prec, Int backend)
{    
        
#ifdef TIMING    
    auto begin = chrono::high_resolution_clock::now();      
#endif
   
//#ifdef HAVE_CUDA
//    cudaDeviceSynchronize();
//#endif
     
    // evaluate the residual R(u) and set it to sys.b
    disc.evalResidual(sys.b, sys.u, backend);

    int N = disc.common.ndof1;

    // residual norm
    dstype oldnrm = PNORM(disc.common.cublasHandle, N, sys.b, backend); 
            
    // construct the preconditioner
    if (disc.common.RBcurrentdim>0) {
        //prec.ConstructPreconditioner(sys, disc, backend);                  
        prec.ComputeInitialGuessAndPreconditioner(sys, disc, backend); 
        
        // v = u + x 
        //int N = disc.common.ndof1;
        ArrayAXPBY(sys.v, sys.u, sys.x, one, one, N, backend);  
        disc.evalResidual(sys.r, sys.v, backend);  
        dstype nrmr = PNORM(disc.common.cublasHandle, N, sys.r, backend);

        if (nrmr>1.05*oldnrm) {
            ArraySetValue(sys.x, zero, disc.common.ndof1, backend);
            // reset the reduced basis
            disc.common.RBremovedind = 0;
            disc.common.RBcurrentdim = 0;
            //ArrayCopy(&prec.precond.W[disc.common.RBremovedind*N], sys.x, N, backend);         
            //disc.common.RBcurrentdim = 1;
            //disc.common.RBremovedind = 1;            
        }

        if (nrmr < disc.common.nonlinearSolverTol) 
            return 1;               
    }    
    else
        ArraySetValue(sys.x, zero, disc.common.ndof1, backend);
    
//   ArraySetValue(sys.x, zero, disc.common.ndof1, backend);
    
#ifdef TIMING        
    auto end = chrono::high_resolution_clock::now();
    disc.common.timing[4] = chrono::duration_cast<chrono::nanoseconds>(end-begin).count()/1e6;        
#endif
    
    // set Wcurrentdim
    //disc.common.Wcurrentdim = disc.common.RBcurrentdim;
    
#ifdef TIMING    
    begin = chrono::high_resolution_clock::now();      
#endif    
    if (disc.common.linearSolver==0) { //GMRES
        disc.common.linearSolverIter = GMRES(sys, disc, prec, backend);  
        if ((disc.common.linearSolverRelError <= disc.common.linearSolverTol*disc.common.linearSolverTolFactor) && (disc.common.mpiRank==0))             
            printf("GMRES converges to the tolerance %g within % d iterations and %d RB dimensions\n",disc.common.linearSolverTol,disc.common.linearSolverIter,disc.common.RBcurrentdim);        
    }
    else { // Conjugate gradient
        disc.common.linearSolverIter = ConjGrad(sys, disc, prec, backend);  
        if ((disc.common.linearSolverRelError <= disc.common.linearSolverTol*disc.common.linearSolverTolFactor) && (disc.common.mpiRank==0))             
            printf("Conjugate Gradient converges to the tolerance %g within % d iterations\n",disc.common.linearSolverTol,disc.common.linearSolverIter);        
    }             
    
#ifdef TIMING        
    end = chrono::high_resolution_clock::now();
    disc.common.timing[5] = chrono::duration_cast<chrono::nanoseconds>(end-begin).count()/1e6;        
        
    if (disc.common.mpiRank==0) {
    printf("--------- Linear Solver Analysis -------\n");    
    printf("Constructing preconditioner time: %g miliseconds\n", disc.common.timing[4]);
    printf("Matrix-vector product time: %g miliseconds\n", disc.common.timing[0]);
    printf("Orthgonalization time: %g miliseconds\n", disc.common.timing[1]);
    printf("Applying preconditioner time: %g miliseconds\n", disc.common.timing[2]);
    printf("Solution update time: %g miliseconds\n", disc.common.timing[3]);
    printf("Linear solver time: %g miliseconds\n\n", disc.common.timing[5]);
        
    printf("--------- Residual Calculation Analysis -------\n");
    printf("Copy to buffsend time: %g miliseconds\n", disc.common.timing[13]);
    printf("Non-blocking send/receive time: %g miliseconds\n", disc.common.timing[6]);
    printf("GetUhat time: %g miliseconds\n", disc.common.timing[7]);
    printf("GetQ (interior elements) time: %g miliseconds\n", disc.common.timing[8]);
    printf("RuElem (interior elements) time: %g miliseconds\n", disc.common.timing[9]);
    printf("MPI_WAITALL time: %g miliseconds\n", disc.common.timing[10]);
    printf("RuElem and GetQ (exterior elements) time: %g miliseconds\n", disc.common.timing[11]);
    printf("RuFace time: %g miliseconds\n", disc.common.timing[12]);    
    printf("Copy from buffrecv time: %g miliseconds\n\n", disc.common.timing[14]);    
    
//     printf("--------- Rq Residual Calculation Analysis -------\n");
//     printf("RqElem time: %g miliseconds\n", disc.common.timing[15]);
//     printf("RqFace time: %g miliseconds\n", disc.common.timing[16]);
//     printf("RqApplyMinv time: %g miliseconds\n", disc.common.timing[17]);
//     printf("RqArrayInsert time: %g miliseconds\n", disc.common.timing[18]);
//     
//     printf("RqFace GetArrayAtIndex xdg time: %g miliseconds\n", disc.common.timing[43]);
//     printf("RqFace Node2Gauss xdg time: %g miliseconds\n", disc.common.timing[19]);
//     printf("RqFace facegeom time: %g miliseconds\n", disc.common.timing[20]);
//     printf("RqFace GetElemNodes uhg time: %g miliseconds\n", disc.common.timing[44]);
//     printf("RqFace Node2Gauss uhg time: %g miliseconds\n", disc.common.timing[21]);
//     printf("RqFace ApplyJacNormal time: %g miliseconds\n", disc.common.timing[22]);
//     printf("RqFace Gauss2Node time: %g miliseconds\n", disc.common.timing[23]);
//     printf("RqFace PutFaceNodes time: %g miliseconds\n", disc.common.timing[24]);
//     
//     printf("RqElem GetArrayAtIndex xdg time: %g miliseconds\n", disc.common.timing[41]);
//     printf("RqElem Node2Gauss xdg time: %g miliseconds\n", disc.common.timing[25]);
//     printf("RqElem elemgeom time: %g miliseconds\n", disc.common.timing[26]);
//     printf("RqElem GetArrayAtIndex udg time: %g miliseconds\n", disc.common.timing[42]);
//     printf("RqElem Node2Gauss udg time: %g miliseconds\n", disc.common.timing[27]);
//     printf("RqElem Gauss2Node time: %g miliseconds\n", disc.common.timing[28]);
//     printf("RqElem PutArrayAtIndex time: %g miliseconds\n\n", disc.common.timing[29]);    
//     
//     printf("--------- Ru Residual Calculation Analysis -------\n");
//     printf("RuFace GetArrayAtIndex xdg time: %g miliseconds\n", disc.common.timing[50]);
//     printf("RuFace Node2Gauss xdg time: %g miliseconds\n", disc.common.timing[30]);    
//     printf("RuFace facegeom time: %g miliseconds\n", disc.common.timing[31]);
//     printf("RuFace GetElemNodes uhg time: %g miliseconds\n", disc.common.timing[51]);
//     printf("RuFace Node2Gauss uhg time: %g miliseconds\n", disc.common.timing[52]);
//     printf("RuFace GetArrayAtIndex udg1 time: %g miliseconds\n", disc.common.timing[53]);
//     printf("RuFace Node2Gauss udg1 time: %g miliseconds\n", disc.common.timing[54]);    
//     printf("RuFace GetArrayAtIndex udg2 time: %g miliseconds\n", disc.common.timing[55]);
//     printf("RuFace Node2Gauss udg2 time: %g miliseconds\n", disc.common.timing[56]);    
//     printf("RuFace GetFaceNodes odg1 time: %g miliseconds\n", disc.common.timing[57]);
//     printf("RuFace Node2Gauss odg1 time: %g miliseconds\n", disc.common.timing[58]);    
//     printf("RuFace GetFaceNodes odg2 time: %g miliseconds\n", disc.common.timing[59]);
//     printf("RuFace Node2Gauss odg2 time: %g miliseconds\n", disc.common.timing[60]);                
//     printf("RuFace FhatDriver time: %g miliseconds\n", disc.common.timing[32]);
//     printf("RuFace FbouDriver time: %g miliseconds\n", disc.common.timing[32]);
//     printf("RuFace ApplyJac1 time: %g miliseconds\n", disc.common.timing[61]);       
//     printf("RuFace Gauss2Node time: %g miliseconds\n", disc.common.timing[34]);
//     printf("RuFace PutFaceNodes time: %g miliseconds\n", disc.common.timing[35]);
//     
//     printf("RuElem GetArrayAtIndex xdg time: %g miliseconds\n", disc.common.timing[45]);
//     printf("RuElem Node2Gauss xdg time: %g miliseconds\n", disc.common.timing[36]);
//     printf("RuElem elemgeom time: %g miliseconds\n", disc.common.timing[37]);
//     printf("RuElem GetArrayAtIndex udg time: %g miliseconds\n", disc.common.timing[46]);
//     printf("RuElem Node2Gauss udg time: %g miliseconds\n", disc.common.timing[47]);    
//     printf("RuElem GetElemNodes odg time: %g miliseconds\n", disc.common.timing[48]);
//     printf("RuElem Node2Gauss odg time: %g miliseconds\n", disc.common.timing[62]);    
//     printf("RuElem GetElemNodes sdg time: %g miliseconds\n", disc.common.timing[63]);
//     printf("RuElem Node2Gauss sdg time: %g miliseconds\n", disc.common.timing[64]);
//     printf("RuElem TdfuncDriver time: %g miliseconds\n", disc.common.timing[65]);
//     printf("RuElem SourceDriver time: %g miliseconds\n", disc.common.timing[66]);
//     printf("RuElem ApplyJac1 time: %g miliseconds\n", disc.common.timing[67]);
//     printf("RuElem Gauss2Node source: %g miliseconds\n", disc.common.timing[38]);
//     printf("RuElem FluxDriver time: %g miliseconds\n", disc.common.timing[39]);
//     printf("RuElem Gauss2Node1 time: %g miliseconds\n", disc.common.timing[40]);    
//     printf("RuElem PutArrayAtIndex time: %g miliseconds\n\n", disc.common.timing[49]); 
    }
#endif
    
    return 0;
    // reset Wcurrentdim
    //disc.common.Wcurrentdim = disc.common.RBcurrentdim;
}

void MGS(cublasHandle_t handle, dstype *V, Int N, Int M, Int m, Int backend)
{            
    dstype scalar;
    for (Int k = 0; k < M; k++) {
        if (k!=m) {
            PDOT(handle, N, &V[m*N], inc1, &V[k*N], inc1, &scalar, backend);         
            ArrayAXPBY(&V[m*N], &V[m*N], &V[k*N], one, -scalar, N, backend);  
        }
    }            
    PDOT(handle, N, &V[m*N], inc1, &V[m*N], inc1, &scalar, backend);     
    scalar = sqrt(scalar);
    ArrayMultiplyScalar(&V[m*N], one/scalar, N, backend);
}

void UpdatePTC(sysstruct &sys, CDiscretization& disc, CPreconditioner& prec, 
        dstype normrold, dstype normrnew, Int backend)
{
//    Int N = disc.common.ndof1;
    
    // update the PTC parameter
    if (disc.common.linearSolverRelError>disc.common.linearSolverTol) 
        // if linear solver does not converge then increase the PTC parameter 
        disc.common.PTCparam = 2*max(normrnew/normrold,normrold/normrnew)*disc.common.PTCparam;
        //disc.common.PTCparam = disc.common.PTCparam;
    else {
        // if linear solver converge then decrease the PTC parameter 
        disc.common.PTCparam = disc.common.PTCparam*(normrnew/normrold)*(normrnew/normrold)/2;                
    }
}

void UpdateRB(sysstruct &sys, CDiscretization& disc, CPreconditioner& prec, Int backend)
{
    Int N = disc.common.ndof1;
                    
    //if (((disc.common.currentstep+1) % 20) == 0) {     
//     if (disc.common.RBcurrentdim==disc.common.RBdim) {
//         // reset the reduced basis after every 100 time steps
//         disc.common.RBremovedind = 0;
//         disc.common.RBcurrentdim = 0;
//         ArrayCopy(&prec.precond.W[disc.common.RBremovedind*N], sys.x, N, backend);          
//         //MGS(disc.common.cublasHandle, prec.precond.W, N, disc.common.RBcurrentdim, disc.common.RBremovedind, backend);
//         disc.common.RBcurrentdim = 1;
//         disc.common.RBremovedind = 1;
//     }
//     else {
        dstype nrmr = PNORM(disc.common.cublasHandle, N, sys.x, backend);
        if (nrmr>zero) {
        // update the reduced basis        
        ArrayCopy(&prec.precond.W[disc.common.RBremovedind*N], sys.x, N, backend);  

        // orthogonalize the reduced basis
        //MGS(disc.common.cublasHandle, prec.precond.W, N, disc.common.RBcurrentdim, disc.common.RBremovedind, backend);

        // update the current dimension of the RB dimension
        if (disc.common.RBcurrentdim<disc.common.RBdim) 
            disc.common.RBcurrentdim += 1;                    

        // update the position of the RB vector to be replaced  
        disc.common.RBremovedind += 1;
        if (disc.common.RBremovedind==disc.common.RBdim) 
            disc.common.RBremovedind = 0;                
        }
    //}
}


Int PTCsolver(sysstruct &sys,  CDiscretization& disc, CPreconditioner& prec, Int backend)       
{
    Int N = disc.common.ndof1;     
    Int it = 0, maxit = disc.common.nonlinearSolverMaxIter;  
    dstype nrmr, tol;
    tol = disc.common.nonlinearSolverTol; // tolerance for the residual
                        
    nrmr = PNORM(disc.common.cublasHandle, N, sys.u, backend);
    if (disc.common.mpiRank==0)
        cout<<"PTC Iteration: "<<it<<",  PTC Param: "<<disc.common.PTCparam<<",  Solution Norm: "<<nrmr<<endl;                                                    
    
    // use PTC to solve the system: R(u) = 0
    for (it=1; it<maxit; it++) {                        
        //nrmrold = nrmr;
        
        // solve the linear system: (lambda*B + J(u))x = -R(u)
        int status;
        status = LinearSolver(sys, disc, prec, backend);
                                
        // update the solution: u = u + x
        ArrayAXPBY(sys.u, sys.u, sys.x, one, one, N, backend); 

// #ifdef HAVE_CUDA
//        cudaDeviceSynchronize();
// #endif         
       
        if (status==1)
           return it;
       
        // compute both the residual vector and sol.udg  
        disc.evalResidual(sys.r, sys.u, backend);
        nrmr = PNORM(disc.common.cublasHandle, N, sys.r, backend);

        if (nrmr > 1.0e6) {                        
            string filename = disc.common.fileout + "_np" + NumberToString(disc.common.mpiRank) + ".bin";                    
            if (disc.common.saveSolOpt==0)
                writearray2file(filename, sys.u, disc.common.ndof1, backend);
            else
                writearray2file(filename, disc.sol.udg, disc.common.ndofudg1, backend);       

            if (disc.common.mpiRank==0)
                cout<<"Residual is NaN in file ptcsolver.cpp at line 301"<<endl;                           
            
            #ifdef  HAVE_MPI       
                MPI_Finalize();    
            #endif
            
            exit(1);
            //error("\nResidual norm in nonlinear solver is NaN.\n");
        }
        
        if (disc.common.mpiRank==0)
            cout<<"PTC Iteration: "<<it<<",  Residual Norm: "<<nrmr<<endl;                           
                        
        // update the reduced basis
        if (status==0)
            UpdateRB(sys, disc, prec, backend);      
        
        // check convergence
        if (nrmr < tol) {            
            return it;   
        }
    }
    
    return it;
}

#endif

