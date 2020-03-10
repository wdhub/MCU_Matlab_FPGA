close all
clear all
%创建 VISA 对象。'ni'为销售商参数，可以为 agilent、NI 或 tek，
%'USB0::0x1AB1::0x04B0::DS2A0000000000::INSTR'为设备的资源描述符。创建后需设置设备的属性，
%本例中设置输入缓存的长度为 2048
MSO2000A = visa( 'ni','USB0::0x1AB1::0x04B0::DS2F210800036::INSTR' );
MSO2000A.InputBufferSize = 2048;
%打开已创建的 VISA 对象
fopen(MSO2000A);
%读取参数
fprintf(MSO2000A,':STOP');
fprintf(MSO2000A,':RUN');
fprintf(MSO2000A,':MEASure:FREQuency? CHANnel%d',1);
Fre=fscanf(MSO2000A);
Fre=str2num(Fre)
fprintf(MSO2000A,':MEASure:VPP? CHANnel%d',1);
Vpp=fscanf(MSO2000A);
Vpp=str2num(Vpp)

%读取波形
fprintf(MSO2000A, ':wav:data?' );
%请求数据
[data,len]= fread(MSO2000A,2048);
%关闭设备
fclose(MSO2000A);
delete(MSO2000A);
clear MSO2000A;
%数据处理。
wave = data(12:len-1);
wave = wave';
subplot(211);
plot(wave);
fftSpec = fft(wave',2048);
fftRms = abs( fftSpec');
fftLg = 20*log(fftRms);
subplot(212);
plot(fftLg);
%总谐波失真
fftEne=fftRms.*fftRms;
total=sqrt(sum(fftEne(1,2:2048)));
THD=total/fftRms(1,1)


