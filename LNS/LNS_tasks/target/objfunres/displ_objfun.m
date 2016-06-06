filename = 'obj_func_vals_temp.csv';
M = csvread(filename);
[d1,d2] = size(M)

% X values
x = csvread(filename,0,0,[0, 0,d1-1, 0]);

% Y values
y = csvread(filename,0,1,[0, 1, d1-1, 1]);

figure
plot(x,y)

title('Weekend objective function value with iterations')
xlabel('Iterations')
ylabel('Objective function value')
legend('Objective function')