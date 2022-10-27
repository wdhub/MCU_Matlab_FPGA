% close all;
% clear all;
samRate=19.2e3;
sym=60;
symNum=6;
alpha=0.5;
filter = rcosdesign(alpha,symNum,sym,'sqrt');

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