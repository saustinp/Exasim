template <typename T> void opuAvfield(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uinf, T *param, T time, int modelnumber, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw, int nce, int npe, int ne, Mutation::Mixture *mix)
{
	double Ustate[6];
	int nspecies = 5;
	int ndim = 2;
	double rho_scale = uinf[0];
	double u_scale = uinf[1];
	double rhoe_scale = uinf[2];

	for (int i = 0; i <ng; i++) {
		int j = i%npe;
		int k = (i-j)/npe;
		T param1 = param[0];
		T param2 = param[1];
		T param15 = param[14];
		T param16 = param[15];
		T param17 = param[16];
		T param18 = param[17];
		T param22 = param[21];
		T param23 = param[22];
		T uinf1 = uinf[0];
		T uinf2 = uinf[1];
		T xdg1 = xdg[j+npe*0+npe*ncx*k];
		T xdg2 = xdg[j+npe*1+npe*ncx*k];
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
		T udg15 = udg[j+npe*14+npe*nc*k];
		T udg16 = udg[j+npe*15+npe*nc*k];
		T udg17 = udg[j+npe*16+npe*nc*k];
		T udg18 = udg[j+npe*17+npe*nc*k];
		T udg19 = udg[j+npe*18+npe*nc*k];
		T udg20 = udg[j+npe*19+npe*nc*k];
		T udg21 = udg[j+npe*20+npe*nc*k];
		T udg22 = udg[j+npe*21+npe*nc*k];
		T udg23 = udg[j+npe*22+npe*nc*k];
		T udg24 = udg[j+npe*23+npe*nc*k];
		T odg1 = odg[j+npe*0+npe*nco*k];
		T odg2 = odg[j+npe*1+npe*nco*k];

		T t1pi = 1.0/3.141592653589793;

		udg1 = udg1*(t1pi*atan(udg1*1.0E+12)+1.0/2.0)+3.182454300088011E-13;
		udg2 = udg2*(t1pi*atan(udg2*1.0E+12)+1.0/2.0)+3.182454300088011E-13;
		udg3 = udg3*(t1pi*atan(udg3*1.0E+12)+1.0/2.0)+3.182454300088011E-13;
		udg4 = udg4*(t1pi*atan(udg4*1.0E+12)+1.0/2.0)+3.182454300088011E-13;
		udg5 = udg5*(t1pi*atan(udg5*1.0E+12)+1.0/2.0)+3.182454300088011E-13;

		double Ucons[8] = {udg1, udg2, udg3, udg4, udg5, udg6, udg7, udg8};
		dimensionalizeConsVars(Ucons, (double*)uinf, nspecies, ndim);
		conservativeToState(Ucons, Ustate, (double*)uinf, nspecies, ndim);
		double rhovec[5] = {Ustate[0],Ustate[1],Ustate[2],Ustate[3],Ustate[4]};
		double rhoe = Ustate[nspecies];

		mix->setState(rhovec, &rhoe, 0);
		uinf1 = mix->P() / rhoe_scale;
		uinf2 = mix->mixtureFrozenGamma();

		T t2 = atan(param22);
		T t3 = param22*udg1;
		T t4 = param22*udg2;
		T t5 = param22*udg3;
		T t6 = param22*udg4;
		T t7 = param22*udg5;
		T t8 = param23*2.0;
		T t9 = param22*param22;
		T t10 = udg1*udg1;
		T t11 = udg2*udg2;
		T t12 = udg3*udg3;
		T t13 = udg4*udg4;
		T t14 = udg5*udg5;
		T t15 = uinf2*2.0;
		T t16 = uinf2+1.0;
		T t22 = 1.0/3.141592653589793;
		T t23 = -param23;
		T t24 = 1.0/param15;
		T t17 = atan(t3);
		T t18 = atan(t4);
		T t19 = atan(t5);
		T t20 = atan(t6);
		T t21 = atan(t7);
		T t25 = t15-2.0;
		T t26 = 1.0/t16;
		T t27 = t3*t3;
		T t28 = t4*t4;
		T t29 = t5*t5;
		T t30 = t6*t6;
		T t31 = t7*t7;
		T t32 = t2*t22;
		T t33 = t32*5.0;
		T t34 = t27+1.0;
		T t35 = t28+1.0;
		T t36 = t29+1.0;
		T t37 = t30+1.0;
		T t38 = t31+1.0;
		T t39 = t17*t22;
		T t40 = t18*t22;
		T t41 = t19*t22;
		T t42 = t20*t22;
		T t43 = t21*t22;
		T t44 = -t32;
		T t45 = -t33;
		T t46 = 1.0/t34;
		T t47 = 1.0/t35;
		T t48 = 1.0/t36;
		T t49 = 1.0/t37;
		T t50 = 1.0/t38;
		T t51 = t39+1.0/2.0;
		T t52 = t40+1.0/2.0;
		T t53 = t41+1.0/2.0;
		T t54 = t42+1.0/2.0;
		T t55 = t43+1.0/2.0;
		T t56 = t51*udg1;
		T t57 = t52*udg2;
		T t58 = t53*udg3;
		T t59 = t54*udg4;
		T t60 = t55*udg5;
		T t61 = t3*t22*t46;
		T t62 = t4*t22*t47;
		T t63 = t5*t22*t48;
		T t64 = t6*t22*t49;
		T t65 = t7*t22*t50;
		T t66 = t51+t61;
		T t67 = t52+t62;
		T t68 = t53+t63;
		T t69 = t54+t64;
		T t70 = t55+t65;
		T t81 = t45+t56+t57+t58+t59+t60+5.0/2.0;
		T t71 = t66*udg9;
		T t72 = t67*udg10;
		T t73 = t68*udg11;
		T t74 = t66*udg17;
		T t75 = t69*udg12;
		T t76 = t67*udg18;
		T t77 = t70*udg13;
		T t78 = t68*udg19;
		T t79 = t69*udg20;
		T t80 = t70*udg21;
		T t82 = 1.0/t81;
		T t83 = t82*t82;
		T t84 = t82*udg8;
		T t85 = t82*uinf1;
		T t86 = t71+t72+t73+t75+t77;
		T t87 = t74+t76+t78+t79+t80;
		T t88 = t84+t85-1.0E-4;
		T t93 = t82*t86*udg6;
		T t94 = t82*t86*udg7;
		T t95 = t82*t87*udg6;
		T t96 = t82*t87*udg7;
		T t89 = param22*t88;
		T t97 = -t93;
		T t98 = -t94;
		T t99 = -t95;
		T t100 = -t96;
		T t105 = -t82*(t93-udg14);
		T t106 = -t82*(t94-udg15);
		T t107 = -t82*(t95-udg22);
		T t108 = -t82*(t96-udg23);
		T t109 = t82*(t95-udg22);
		T t117 = -param22*(-t23+t82*(t93-udg14)+t82*(t96-udg23));
		T t90 = atan(t89);
		T t101 = t97+udg14;
		T t102 = t98+udg15;
		T t103 = t99+udg22;
		T t104 = t100+udg23;
		T t114 = t106+t109;
		T t115 = t23+t105+t108;
		T t116 = pow(t107+t82*(t94-udg15),2.0);
		T t118 = atan(t117);
		T t91 = t22*t90;
		T t119 = sqrt(t116);
		T t122 = t22*t118;
		T t92 = t91+1.0/2.0;
		T t120 = param22*t119;
		T t124 = t122-1.0/2.0;
		T t110 = t88*t92;
		T t121 = atan(t120);
		T t126 = -t124*(-t23+t82*(t93-udg14)+t82*(t96-udg23));
		T t127 = t124*(-t23+t82*(t93-udg14)+t82*(t96-udg23));
		T t111 = t44+t110+5.001E-1;
		T t123 = t22*t121;
		T t130 = t8+t32+t127-1.0/2.0;
		T t112 = t25*t26*t111;
		T t125 = t123+1.0/2.0;
		T t131 = param22*t130;
		T t113 = 1.0/sqrt(t112);
		T t128 = t119*t125;
		T t132 = atan(t131);
		T t129 = -t128;
		T t135 = t22*t132;
		T t133 = param23+t32+t129-1.0/2.0;
		T t138 = t135-1.0/2.0;
		T t134 = param22*t133;
		T t140 = t130*t138;
		T t136 = atan(t134);
		T t143 = param23+t127+t140;
		T t137 = t22*t136;
		T t144 = t143*t143;
		T t145 = t143*t143*t143;
		T t139 = t137-1.0/2.0;
		T t141 = t133*t139;
		T t142 = -t141;
		T t146 = t128+t142;
		T t147 = t146*t146;
		T t148 = t144+t147+1.0E-16;
		T t149 = 1.0/t148;
		T t150 = odg2*t24*t113*t145*t149;
		T t151 = -t150;
		T t152 = param17+t151;
		T t153 = param22*t152;
		T t154 = atan(t153);
		T t155 = t22*t154;
		T t156 = t155-1.0/2.0;
		T t157 = t152*t156;
		T t158 = -t157;
		T t159 = param18+t32+t158-1.0/2.0;
		f[j+npe*0+npe*nce*k] = odg2*param16*t24*t81*(t157-t159*(t22*atan(param22*t159)-1.0/2.0))*sqrt(t112+t83*(udg6*udg6)+t83*(udg7*udg7));
	}
}

template void opuAvfield(double *, double *, double *, double *, double *, double *, double *, double, int, int, int, int, int, int, int, int, int, int, int, Mutation::Mixture *);
template void opuAvfield(float *, float *, float *, float *, float *, float *, float *, float, int, int, int, int, int, int, int, int, int, int, int, Mutation::Mixture *);
