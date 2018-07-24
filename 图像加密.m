Img=imread('C:\Users\lxylovelb\Desktop\1.jpg');
>> Double_Img=double(Img);
>> fileID=fopen('C:\Users\lxylovelb\Desktop\message.txt','r');
>> [msg,len]=fread(fileID,'ubit1');
>> [m,n]=size(Double_Img);
>> p=1;
>> for f2=1:n
for f1=1:m
Double_Img(f1,f2)=Double_Img(f1,f2)-mod(Double_Img(f1,f2),2)+msg(p,1);
if p==len
break;
end
p=p+1;
end
if p==len
break;
end
end
>> Double_Img=uint8(Double_Img); 
>> imwrite(Double_Img,'C:\Users\lxylovelb\Desktop\2.jpg');
>> subplot(121);imshow(Img);title('原图片');
>> subplot(122);imshow(Double_Img);title('嵌入信息后的图片');
