filename = 'objfcn.csv';
M = csvread(filename);
[d1,d2] = size(M)


% Y values
y = csvread(filename,0,0,[0, 0,d1-1, 0])

% X values
x = 1:d1;
x = x'
close all
plot(x,y)
title('Weekend objective function','FontSize',10)
xlabel('Iterations')
ylabel('Objective function value')
legend('Objective function')


% si_y = csvread(filename,0,2,[0, 2, d1-1, 2]);
% s_y = csvread(filename,0,3,[0, 3, d1-1, 3]);
% d_y = csvread(filename,0,4,[0, 4, d1-1, 4]);
% 
% av_si_y = csvread(filename,0,5,[0, 5, d1-1, 5]);
% av_s_y = csvread(filename,0,6,[0, 6, d1-1, 6]);
% av_d_y = csvread(filename,0,7,[0, 7, d1-1, 7]);
% 
% SI_S = [si_y, s_y];
% R_SI_S = corrcoef(SI_S)
% SI_D = [si_y, d_y];
% R_SI_D = corrcoef(SI_D)
% S_D = [s_y, d_y];
% R_S_D = corrcoef(S_D)
% 
% close all
% 
% figure
% plot(x,y)
% 
% title('Weekend objective function','FontSize',28)
% xlabel('Iterations')
% ylabel('Objective function value')
% legend('Objective function')
% set(gca,'fontsize', 20);
% 
% 
% figure
% plot(x,si_y,x,s_y,x,d_y)
% legend('Stand in min cost', 'Shift avail min cost', 'Day avail min cost')
% xlabel('Iterations')
% ylabel('Objective function component value')
% title('Weekend objective function cost components - min costs')
% set(gca,'fontsize', 20);
% 
% figure
% plot(x,av_si_y,x,av_s_y,x,av_d_y)
% legend('Stand in aver cost', 'Shift avail aver cost', 'Day avail aver cost')
% xlabel('Iterations')
% ylabel('Objective function component value')
% title('Weekend objective function cost components - average costs')
% set(gca,'fontsize', 20);