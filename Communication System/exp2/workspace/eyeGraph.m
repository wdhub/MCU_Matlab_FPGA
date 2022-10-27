blk=30;
[~,~,l]=size(out.baseband1.Data);
seg=reshape(out.baseband1.Data,1,l);
aa=floor(l/blk);
l=aa*blk;
seg=seg(1,1:l);
for ii=1:aa
   temp=(ii-1)*blk+1:ii*blk;
   plot(seg(1,temp)) 
   hold on
end
