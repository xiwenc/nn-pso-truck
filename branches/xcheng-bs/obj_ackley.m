function ackley = obj_ackley(swarm, args)
% obj_ackley(args ,x)	Implements the Ackley function
%   args.c1
%   args.c2
%   args.c3

c1 = args.c1;
c2 = args.c2;
c3 = args.c3;

[population, dim] = size(swarm);
ackley = (-c1*exp(-c2*sqrt(1/dim*sum((swarm.^2)')))-exp(1/dim*sum(cos((swarm .*c3)')))+c1+exp(1))';
