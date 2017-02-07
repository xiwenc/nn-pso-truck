%The Rastrigrin function for use with the psotoolbox
%
% Function Description:
% Equation ->  sum (x(i)^2 - 10 * cos(2 * pi * x(i)) + 10)
%      xmin  = [0, 0, 0.....0]  (all zeoes)
%      fxmin = 0                  (zero)
function Rastred = obj_rastrigrin(Swarm, args)
[SwarmSize, Dim] = size(Swarm);
Rastred = Dim * 10 + sum(((Swarm .^2) - 10 * cos(2 * pi * Swarm))')';

