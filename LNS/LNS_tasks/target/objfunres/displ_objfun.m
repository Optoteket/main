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
R_SI_S = corrcoef(SI_S)
SI_D = [si_y, d_y];
R_SI_D = corrcoef(SI_D)
S_D = [s_y, d_y];
R_S_D = corrcoef(S_D)

close all

figure
plot(x,y)

title('Weekend objective function value')
xlabel('Iterations')
ylabel('Objective function value')
legend('Objective function')

figure
%scatter(si_y,s_y, 'filled')
plot(x,si_y,x,s_y,x,d_y)
legend('Stand in cost', 'Shift avail cost', 'Day avail cost')
xlabel('Iterations')
ylabel('Objective function component value')
title('Weekend objective function cost components')
%plot(x,s_y)
%plot(x,d_y)