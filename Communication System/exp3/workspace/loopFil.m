%% initial
Fs=60*19.2e3;%60
Ts=1/Fs;
f_c=100e3;
Gc=1;
Gg=1.5;
f_nco=100e3;
f_nco2=150e3;
f_src=19.2e3;
Kc=Gc/4*Fs/2^16;
Kg=Gg/4*Fs/2^16;
%% filter constants
[ac,bc] = loopFilter(Ts,Kc);
[ag,bg] = loopFilter(Ts,Kg);
%% NCO
inc=2^16*f_nco/Fs;
inc2=2^16*f_nco2/Fs;
inc_src=2^16*f_src/Fs;
%% plot
% freqz(b,a);
%% rcosfilter
samRate=19.2e3;
sym=60;%60
symNum=6;
alpha=0.5;
filter = rcosdesign(alpha,symNum,sym,'sqrt');