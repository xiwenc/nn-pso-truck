function [] = main(objfunc, dim, n, s, i)
runs = 20;

args.c1 = 20;
args.c2 = 0.2;
args.c3 = 2*pi;
vmax = 1;
xmax = 10;

mruns(runs, objfunc, args, dim, n, s, i, vmax, xmax);
end
