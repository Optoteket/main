%%
filename = '500_20_run/weekend_AMPL_data_mod.csv';
M = csvread(filename);
[d1,d2] = size(M)

Wend_obj_fun = csvread(filename,0,0,[0,0,d1-1, 0]);
Heur_cost = csvread(filename,0,3,[0,3,d1-1, 3]);
AMPL_cost = csvread(filename,0,7,[0,7,d1-1, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)

mean(Heur_cost)

%%

filename = 'weights_run/weekend_AMPL_data_mod.csv';
M = csvread(filename);
[d1,d2] = size(M)

% Weights  1 1 1
Wend_obj_fun = csvread(filename,0,0,[0,0,100, 0]);
Heur_cost = csvread(filename,0,3,[0,3,100, 3]);
AMPL_cost = csvread(filename,0,7,[0,7,100, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
mean(Heur_cost)

% Weights 10 1 1
Wend_obj_fun = csvread(filename,101,0,[101,0,200, 0]);
Heur_cost = csvread(filename,101,3,[101,3,200, 3]);
AMPL_cost = csvread(filename,101,7,[101,7,200, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
mean(Heur_cost)

% Weights 1 10 1
Wend_obj_fun = csvread(filename,201,0,[201,0,300, 0]);
Heur_cost = csvread(filename,201,3,[201,3,300, 3]);
AMPL_cost = csvread(filename,201,7,[201,7,300, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
mean(Heur_cost)

% Weights 0 0 0
Wend_obj_fun = csvread(filename,301,0,[301,0,400, 0]);
Heur_cost = csvread(filename,301,3,[301,3,400, 3]);
AMPL_cost = csvread(filename,301,7,[301,7,400, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
mean(Heur_cost)