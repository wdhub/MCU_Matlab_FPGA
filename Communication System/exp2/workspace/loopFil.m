%% initial
Fs=6*19.2e3;
Ts=1/Fs;
G=64;
K=G/4*Fs/2^16;
%% filter constants
[C1,C2] = loopFilter(Ts,K);
temp=C2-C1;
b=[C1,temp];
b=double(b);
a=[1,-1];
%% plot
% freqz(b,a);
%% rcosfilter
samRate=19.2e3;
sym=6;
symNum=6;
alpha=0.5;
filter = rcosdesign(alpha,symNum,sym,'sqrt');