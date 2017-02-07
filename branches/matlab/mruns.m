function [] = mruns(runs, objfunc, args, dim, n, s, i, vmax, xmax)
% [] = mruns(runs, objfunc, args, dim, n, s, i, vmax, xmax)
% Executes multiple runs of BS/PSO/GA and plot them

so = s;
prefix ='output/';

% the runs...
for t=1:runs
    
    % BS + GA0
    s = so;
    ga = 0;
    [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, ga);
    stats.bs0(t,:) = history;

    % BS + GA1
    s = so;
    ga = 1;
    [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, ga);
    stats.bs1(t,:) = history;

    % BS + GA2
    s = so;
    ga = 2;
    [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, ga);
    stats.bs2(t,:) = history;

    % PSO
    s = n;
    ga = 0;
    [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, ga);
    stats.pso(t,:) = history;

    % GA
    s = 0;
    ga = 0;
    [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, ga);
    stats.ga0(t,:) = history;

    % GA1
    s = 0;
    ga = 1;
    [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, ga);
    stats.ga1(t,:) = history;

    % GA2
    s = 0;
    ga = 2;
    [fxmin, xmin, history] = bs(objfunc, args, dim, n, s, i, vmax, xmax, ga);
    stats.ga2(t,:) = history;

end

x = 1:1:i;
whitebg;

% each algo and its mean, max and min
data = stats.bs0;
semilogy(x, mean(data), 'b-.', x, min(data), 'c-', x, max(data), 'r-.');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-bs0.eps');
xlabel('evaluations');
ylabel('fitness');
legend('Mean', 'Min', 'Max');
print('-depsc', fname);

data = stats.bs1;
semilogy(x, mean(data), 'b-.', x, min(data), 'c-', x, max(data), 'r-.');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-bs1.eps');
xlabel('evaluations');
ylabel('fitness');
legend('Mean', 'Min', 'Max');
print('-depsc', fname);

data = stats.bs2;
semilogy(x, mean(data), 'b-.', x, min(data), 'c-', x, max(data), 'r-.');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-bs2.eps');
xlabel('evaluations');
ylabel('fitness');
legend('Mean', 'Min', 'Max');
print('-depsc', fname);

data = stats.ga0;
semilogy(x, mean(data), 'b-.', x, min(data), 'c-', x, max(data), 'r-.');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-ga0.eps');
xlabel('evaluations');
ylabel('fitness');
legend('Mean', 'Min', 'Max');
print('-depsc', fname);

data = stats.ga1;
semilogy(x, mean(data), 'b-.', x, min(data), 'c-', x, max(data), 'r-.');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-ga1.eps');
xlabel('evaluations');
ylabel('fitness');
legend('Mean', 'Min', 'Max');
print('-depsc', fname);

data = stats.ga2;
semilogy(x, mean(data), 'b-.', x, min(data), 'c-', x, max(data), 'r-.');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-ga2.eps');
xlabel('evaluations');
ylabel('fitness');
legend('Mean', 'Min', 'Max');
print('-depsc', fname);

data = stats.pso;
semilogy(x, mean(data), 'b-.', x, min(data), 'c-', x, max(data), 'r-.');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-pso.eps');
xlabel('evaluations');
ylabel('fitness');
legend('Mean', 'Min', 'Max');
print('-depsc', fname);

% all algos compared: std, min and mean
semilogy(x, mean(stats.bs0), 'b-.', x, mean(stats.pso), 'm-', x, mean(stats.ga0), 'b-', x, mean(stats.bs1), 'c-.', x, mean(stats.ga1), 'c-', x, mean(stats.bs2), 'r-.', x, mean(stats.ga2), 'r-');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-all-mean.eps');
xlabel('evaluations');
ylabel('fitness');
legend('BS0', 'PSO', 'GA0', 'BS1', 'GA1', 'BS2', 'GA2');
print('-depsc', fname);

semilogy(x, min(stats.bs0), 'b-.', x, min(stats.pso), 'm-', x, min(stats.ga0), 'b-', x, min(stats.bs1), 'c-.', x, min(stats.ga1), 'c-', x, std(stats.bs2), 'r-.', x, std(stats.ga2), 'r-');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-all-min.eps');
xlabel('evaluations');
ylabel('fitness');
legend('BS0', 'PSO', 'GA0', 'BS1', 'GA1', 'BS2', 'GA2');
print('-depsc', fname);

plot(x, std(stats.bs0), 'b-.', x, std(stats.pso), 'm-', x, std(stats.ga0), 'b-', x, std(stats.bs1), 'c-.', x, std(stats.ga1), 'c-', x, std(stats.bs2), 'r-.', x, std(stats.ga2), 'r-');
fname = strcat(prefix, objfunc, '-d', num2str(dim), '-s', num2str(so), '-n', num2str(n), '-all-std.eps');
xlabel('evaluations');
ylabel('fitness');
legend('BS0', 'PSO', 'GA0', 'BS1', 'GA1', 'BS2', 'GA2');
print('-depsc', fname);


end
