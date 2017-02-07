function [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, mode)
% [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, ga)
% objfunc   = name of objective function to be minimized
% args      = set of constant args passed to objfunc
% dim       = dimension of an individual
% n         = population size
% s         = survivors, where:
%       s == 0      -> GA with VPAC
%       s == n      -> plain PSO
%       0 < s < n   -> BS
% i         = number of iterations to run
% vmax      = maximum velocity
% xmax      = maximum x
% mode      = where:
%       mode == 0 -> VPAC only
%       mode == 1 -> uniform crossover only
%       mode == 2 -> VPAC then uniform crossover
%       otherwise -> no crossover at all

options.inertia.begin = 0.7;
options.inertia.last = 0.4;
options.mrate = 1.0;
options.dimensions = dim;
options.population = n;
options.survivors = s;
options.memory = 2.0;
options.social = 2.0;
options.iterations = i;
options.vmax = vmax;
options.xmax = xmax;
options.objective = objfunc;
%options.objective = 'obj_ackley';
%options.objective = 'obj_griewank';

%options.args.c1 = 20;
%options.args.c2 = 0.2;
%options.args.c3 = 2*pi;
options.args = args;

% internal vars
iter = 1;
step.mrate = options.mrate / options.iterations;
step.inertia = (options.inertia.begin - options.inertia.last) / options.iterations;
inertia = options.inertia.begin;
mrate = options.mrate;
survivors = options.survivors;
discard = options.population - survivors;
ga_only = 0;

% init swarm
swarm = rand(options.population, options.dimensions) * options.xmax;
velocity = rand(options.population, options.dimensions) * options.vmax;

% init personal best
fitness = feval(options.objective, swarm, options.args);
pbest = swarm;
fpbest = fitness;

% init global best
[fgbest, gi] = min(fpbest);
gbest = pbest(gi,:);

history(iter) = fgbest;

while ( iter < options.iterations )
    iter = iter + 1;

    % rank the individuals
    [fitness, isorted] = sort(fitness);
    for i=1:options.population
        swarm(i,:) = swarm(isorted(i),:);
        pbest(i,:) = pbest(isorted(i),:);
        fpbest(i,:) = fpbest(isorted(i),:);
        velocity(i,:) = velocity(isorted(i),:);
    end

    % keep old velocities for GA
    velocity2 = velocity;
    % grow gbest for easy calculations
    gb = repmat(swarm(gi,:), options.population, 1);

    R1 = randn(options.population, options.dimensions);
    R2 = randn(options.population, options.dimensions);

    % update velocity
    velocity = velocity * inertia + options.memory*R1.*(pbest-swarm) + options.social*R2.*(gb-swarm);
    % enfore vmax
    bigger = velocity > options.vmax;
    velocity(find(bigger)) = options.vmax;
    smaller = velocity < -options.vmax;
    velocity(find(smaller)) = -options.vmax;

    % if survivors == 0 we assume GA only
    if survivors == 0
        ga_only = 1;
    else
        % discard 
        for i=survivors+1:options.population
            swarm(survivors+1,:) = [];
            pbest(survivors+1,:) = [];
            fpbest(survivors+1,:) = [];
            velocity(survivors+1,:) = [];
            velocity2(survivors+1,:) = [];
        end
    end

    % do GA
    if discard > 0
        if ga_only == 1
            count = floor(discard/2); % 50% of best individuals survive
        else
            count = survivors;
            %velocity2 = velocity; % original BS
        end

        % tournament selection
        for i=1:discard
            p1 = floor(rand() * count) + 1;
            p2 = floor(rand() * count) + 1;
            % p2 != p1
            if p2 == p1
                p2 = p1 + 1;
                if p2 > count
                    p2 = 1;
                end
            end
            
            % grab winner
            if fitness(p1) < fitness(p2)
                winner = p1;
            else
                winner = p2;
            end

            ga.swarm(i,:) = swarm(winner,:);
            ga.velocity(i,:) = velocity2(winner,:);
            ga.pbest(i,:) = pbest(winner,:);
            ga.fpbest(i,:) = fpbest(winner,:);
        end

        % crossover
        for i=1:discard
            p1 = i;
            p2 = i+1;
            if p2 > discard
                p2 = 1;
            end

            % do VPAC for mode 0 and 2
            if mode == 2 || mode == 0
                temp = (ga.swarm(p1,:) + ga.swarm(p2,:)) / 2;
                o1 = temp - ga.velocity(p1,:) * rand();
                o2 = temp - ga.velocity(p2,:) * rand();
            else
                o1 = ga.swarm(p1,:);
                o2 = ga.swarm(p2,:);
            end

            % do uniform when mode is 2 or 1
            if mode == 2 || mode == 1
                % increase diversity using uniform crossover
                for u=1:options.dimensions
                    if rand() > 0.5
                        temp = o1(u);
                        o1(u) = o2(u);
                        o2(u) = temp;
                    end
                end
            end

            ga.swarm(p1,:) = o1;
            ga.swarm(p2,:) = o2;
            i = i + 2;
        end

        % mutate
        for i=1:discard
            for j=1:options.dimensions
                if rand() < mrate
                    ga.swarm(i,j) = ga.swarm(i,j) * rand();
                end
            end
        end
    end


    if ga_only ~= 1
        % PSO
        % update location
        swarm = swarm + velocity;
    end

    % merge ga into swarm
    j = 1;
    for i=survivors+1:options.population
        swarm(i,:) = ga.swarm(j,:);
        velocity(i,:) = ga.velocity(j,:);
        pbest(i,:) = ga.pbest(j,:);
        fpbest(i,:) = ga.fpbest(j,:);
        j = j + 1;
    end

    % evaluate particles
    fitness = feval(options.objective, swarm, options.args);

    % update pbest
    better = fitness < fpbest;
    fpbest(find(better)) = fitness(find(better));
    pbest(find(better),:) = swarm(find(better),:);

    % update gbest
    [nfgbest, gi] = min(fpbest);
    if nfgbest < fgbest
        fgbest = nfgbest;
        gbest = pbest(gi,:);
    end

    % if only GA, display best of current generation
    if ga_only == 1
        [nfgbest, gi] = min(fpbest);
        fgbest = nfgbest;
        gbest = pbest(gi,:);
    end

    % history
    history(iter) = fgbest;

    % inertia and mrate decrease over time
    inertia = inertia - step.inertia;
    mrate = mrate - step.mrate;
end

%[nfgbest, gi] = min(fpbest);
%fxmin = nfgbest;
%xmin = pbest(gi,:);
fxmin = fgbest;
xmin = gbest;
history;

end
