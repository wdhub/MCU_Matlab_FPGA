function [C1,C2] = loopFilter(Ts,K)
%This function gnereate the C1,C2 of loop filter according to sample rate
%and loop gain.
syms t1 t2 
damp=0.707;
cutoff=5000;
equ1=damp==(t2/2)*sqrt(K/t1);
equ2=cutoff==sqrt(2/(t1^2-2*t2^2));
S=solve([equ1,equ2],[t1,t2]);
t1=vpa(S.t1);
t2=vpa(S.t2);
t1=max(t1);%positive solution
t2=max(t2);%positive solution
C1=(2*t2+Ts)/(2*t1);
C2=Ts/t1;
end

