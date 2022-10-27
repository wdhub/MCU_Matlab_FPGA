% close all;
% clear all;
samRate=19.2e3;
sym=6;
symNum=6;
for ii=1:3
alpha=ii*0.25;
filter(ii,:) = rcosdesign(alpha,symNum,sym,'sqrt');
end
% fvtool(filter,'analysis','impulse');
% fvtool(filter,'analysis','magnitude');
% hold on;
% 
% alpha=0.5;
% samRate=19.2e3;
% sym=16;
% symNum=16;
% filter= rcosdesign(alpha,symNum,sym,'normal');
% fvtool(filter,'analysis','impulse');
% fvtool(filter,'analysis','magnitude');