filename = 'obj_func_vals_temp.csv';
M = csvread(filename);
[d1,d2] = size(M)

% X values
x = csvread(filename,0,0,[0, 0,d1-1, 0]);

% Y values
y = csvread(filename,0,1,[0, 1, d1-1, 1]);
si_y = csvread(filename,0,2,[0, 2, d1-1, 2]);
s_y = csvread(filename,0,3,[0, 3, d1-1, 3]);
d_y = csvread(filename,0,4,[0, 4, d1-1, 4]);

SI_S = [si_y, s_y];
corrcoef(SI_S)
SI_S = [si_y, s_y];
corrcoef(SI_S)


close all

figure
plot(x,y)

title('Weekend objective function value with iterations')
xlabel('Iterations')
ylabel('Objective function value')
legend('Objective function')

figure
%scatter(si_y,s_y, 'filled')
plot(x,si_y,x,s_y,x,d_y)
legend('Stand in cost', 'Shift avail cost', 'Day avail cost')
%plot(x,s_y)
%plot(x,d_y)