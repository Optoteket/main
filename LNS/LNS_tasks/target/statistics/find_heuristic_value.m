filename = '1000_10_run/weekend_AMPL_data_mod.csv';
M = csvread(filename);
[d1,d2] = size(M)

Heur_cost = csvread(filename,0,3,[0,3,d1-1, 3]);

mean(Heur_cost)