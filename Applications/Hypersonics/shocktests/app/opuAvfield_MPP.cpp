template <typename T> void opuAvfield(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uinf, T *param, T time, int modelnumber, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw, int nce, int npe, int ne, Mutation::Mixture *mix)
{
	// std::cout << "begin avfield" << std::endl;
	for (int i = 0; i <ng; i++) {
		int j = i%npe;
		int k = (i-j)/npe;
		T param1 = param[0];
		T param15 = param[14];
		T param16 = param[15];
		T param17 = param[16];
		T param18 = param[17];
		T xdg1 = xdg[j+npe*0+npe*ncx*k];
		T udg1 = udg[j+npe*0+npe*nc*k];
		T udg2 = udg[j+npe*1+npe*nc*k];
		T udg3 = udg[j+npe*2+npe*nc*k];
		T udg4 = udg[j+npe*3+npe*nc*k];
		T udg5 = udg[j+npe*4+npe*nc*k];
		T udg6 = udg[j+npe*5+npe*nc*k];
		T udg7 = udg[j+npe*6+npe*nc*k];
		T udg8 = udg[j+npe*7+npe*nc*k];
		T udg9 = udg[j+npe*8+npe*nc*k];
		T udg10 = udg[j+npe*9+npe*nc*k];
		T udg11 = udg[j+npe*10+npe*nc*k];
		T udg12 = udg[j+npe*11+npe*nc*k];
		T udg13 = udg[j+npe*12+npe*nc*k];
		T udg14 = udg[j+npe*13+npe*nc*k];
		T odg1 = odg[j+npe*0+npe*nco*k];
		T odg2 = odg[j+npe*1+npe*nco*k];

		T t1pi = 1.0/3.141592653589793;
		udg1 = udg1*(t1pi*atan(udg1*1.0E+3)+1.0/2.0)+3.183097800805168E-4;
		udg2 = udg2*(t1pi*atan(udg2*1.0E+3)+1.0/2.0)+3.183097800805168E-4;
		udg3 = udg3*(t1pi*atan(udg3*1.0E+3)+1.0/2.0)+3.183097800805168E-4;
		udg4 = udg4*(t1pi*atan(udg4*1.0E+3)+1.0/2.0)+3.183097800805168E-4;
		udg5 = udg5*(t1pi*atan(udg5*1.0E+3)+1.0/2.0)+3.183097800805168E-4;

		int nspecies = 5;
		double rho_scale = uinf[0];
		double u_scale = uinf[1];
		double rhoe_scale = uinf[2];

		double Ucons[7] = {udg1, udg2, udg3, udg4, udg5, udg6, udg7};
		double Ustate[6];
		dimensionalizeConsVars(Ucons, (double*)uinf, nspecies, 1);
		conservativeToState(Ucons, Ustate, (double*)uinf, nspecies);
		double rhovec[5] = {Ustate[0],Ustate[1],Ustate[2],Ustate[3],Ustate[4]};
		double rhoe = Ustate[nspecies];
		mix->setState(rhovec, &rhoe, 0);

		T uinf1 = mix->P()/rhoe_scale; // pressure
		T uinf2 = mix->mixtureFrozenGamma(); // gamma

		T t2 = uinf2*2.0;
		T t3 = uinf2+1.0;
		T t4 = 1.0/3.141592653589793;
		T t5 = 1.0/param15;
		T t8 = udg8+udg9+udg10+udg11+udg12;
		T t9 = param17*1.0E+3;
		T t10 = udg1*1.0E+3;
		T t11 = udg2*1.0E+3;
		T t12 = udg3*1.0E+3;
		T t13 = udg4*1.0E+3;
		T t14 = udg5*1.0E+3;
		T t6 = t2-2.0;
		T t7 = 1.0/t3;
		T t15 = atan(t10);
		T t16 = atan(t11);
		T t17 = atan(t12);
		T t18 = atan(t13);
		T t19 = atan(t14);
		T t20 = t4*t15;
		T t21 = t4*t16;
		T t22 = t4*t17;
		T t23 = t4*t18;
		T t24 = t4*t19;
		T t25 = t20+1.0/2.0;
		T t26 = t21+1.0/2.0;
		T t27 = t22+1.0/2.0;
		T t28 = t23+1.0/2.0;
		T t29 = t24+1.0/2.0;
		T t30 = t25*udg1;
		T t31 = t26*udg2;
		T t32 = t27*udg3;
		T t33 = t28*udg4;
		T t34 = t29*udg5;
		T t35 = t30+t31+t32+t33+t34+1.591548900402584E-3;
		T t36 = 1.0/t35;
		T t37 = t36*udg7;
		T t38 = t36*uinf1;
		T t41 = t8*t36*udg6;
		T t39 = t37*1.0E+3;
		T t40 = t38*1.0E+3;
		T t42 = -t41;
		T t44 = -t36*(t41-udg13);
		T t45 = t37+t38-1.0E-4;
		T t46 = t36*(t41-udg13)*-1.0E+3;
		T t43 = t42+udg13;
		T t47 = t39+t40-1.0/1.0E+1;
		T t49 = t44-1.0E+4;
		T t51 = t46-1.0E+7;
		T t48 = atan(t47);
		T t52 = atan(t51);
		T t50 = t4*t48;
		T t54 = t4*t52;
		T t53 = t50+1.0/2.0;
		T t55 = t54-1.0/2.0;
		T t56 = t45*t53;
		T t57 = -t55*(t36*(t41-udg13)+1.0E+4);
		T t58 = t55*(t36*(t41-udg13)+1.0E+4);
		T t59 = t58*-1.0E+3;
		T t60 = t56+4.183097800805168E-4;
		T t63 = t57-1.999999968169022E+4;
		T t61 = t6*t7*t60;
		T t64 = t59-1.999999968169022E+7;
		T t62 = 1.0/sqrt(t61);
		T t65 = atan(t64);
		T t66 = t4*t65;
		T t67 = t66+1.0/2.0;
		T t68 = -t67*(t58+1.999999968169022E+4);
		T t69 = t58+t68+1.0E+4;
		T t70 = odg2*t5*t62*t69;
		T t71 = -t70;
		T t73 = t70*1.0E+3;
		T t72 = param17+t71;
		T t74 = -t73;
		T t75 = t9+t74;
		T t76 = atan(t75);
		T t77 = t4*t76;
		T t78 = t77-1.0/2.0;
		T t79 = t72*t78;
		f[j+npe*0+npe*nce*k] = odg2*param16*t5*(fabs(udg6)/fabs(t35)+sqrt(fabs(t6*t60)/fabs(t3)))*(t79-(t4*atan(param18*-1.0E+3+t79*1.0E+3+3.183097800805168E-1)+1.0/2.0)*(-param18+t79+3.183097800805168E-4));
	}
	// std::cout << "end avfield" << std::endl;
}

template void opuAvfield(double *, double *, double *, double *, double *, double *, double *, double, int, int, int, int, int, int, int, int, int, int, int, Mutation::Mixture *);
template void opuAvfield(float *, float *, float *, float *, float *, float *, float *, float, int, int, int, int, int, int, int, int, int, int, int, Mutation::Mixture *);
