close all


my_image = fspecial('gaussian', 500, 125);
my_image = (my_image .- min(my_image(:))) ./ (max(my_image(:)) - min(my_image(:)));
figure;
surf(my_image,'EdgeColor','None');
xlabel ("x");
ylabel ("y");
zlabel ("f(x,y)");
title("Example of 2D function")
%print -deps -color -F:23 '2D_function1.eps'
print -dpng -color -F:23 '2D_function1.png'
%print -dpdf -color -F:23 '2D_function1.pdf'



figure;imagesc(my_image);colormap gray;
xlabel ("x");
ylabel ("y");
print -deps -color -F:23 '2D_function2.eps'
print -dpng -color -F:23 '2D_function2.png'
%print -dpdf -color -F:23 '2D_function2.pdf'



x = [1:size(my_image,1)];
norm = my_image((size(my_image,1)/2),:);
figure;
plot(x,norm, 'Linewidth', 3)
xlabel ("x");
ylabel ("f(x)");
title("Example of 1D function")
print -deps -color -F:23 '1D_function.eps'
print -dpdf -color -F:23 '1D_function.pdf'




for i = 1:64
    my_image=rand(512);
    square=ones(64, 64);
    new_image=my_image;
    new_image(i*2:i*2+size(square,1)-1,i*2:i*2+size(square,2)-1)=square;
    %figure;imagesc(new_image);

    filename=sprintf('./video/video%02d.png',i);

    imwrite(new_image, filename);
end

