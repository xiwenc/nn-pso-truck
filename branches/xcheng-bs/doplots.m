function [] = doplot()
% plots the objective functions

args.c1 = 20;
args.c2 = 0.2;
args.c3 = 2*pi;

[x,y]=meshgrid(-5:0.1:5,-5:0.1:5);

for i=1:size(x,2)
    for j=1:size(y,1)
        data.ackley(i,j) = obj_ackley([x(1,i), y(j,1)], args);
        data.rastrigrin(i,j) = obj_rastrigrin([x(1,i), y(j,1)], args);
        data.griewank(i,j) = obj_griewank([x(1,i), y(j,1)], args);
        data.rosenbrock(i,j) = obj_rosenbrock([x(1,i), y(j,1)], args);
    end
end
surf(x,y,data.ackley);
print('-depsc', 'fig-ackley.eps');

surf(x,y,data.rastrigrin);
print('-depsc', 'fig-rastrigrin.eps');

surf(x,y,data.griewank);
print('-depsc', 'fig-griewank.eps');

surf(x,y,data.rosenbrock);
print('-depsc', 'fig-rosenbrock.eps');

end
