
filename = 'complete_run/weekend_AMPL_data_mod.csv';
M = csvread(filename);
[d1,d2] = size(M)

% It: 10/10
Wend_obj_fun = csvread(filename,0,0,[0,0,100, 0]);
Heur_cost = csvread(filename,0,3,[0,3,100, 3]);
AMPL_cost = csvread(filename,0,7,[0,7,100, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
m_10_10=mean(Heur_cost)

% It: 50/10
Wend_obj_fun = csvread(filename,101,0,[101,0,200, 0]);
Heur_cost = csvread(filename,101,3,[101,3,200, 3]);
AMPL_cost = csvread(filename,101,7,[101,7,200, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
m_50_10=mean(Heur_cost)

% It: 100/10
Wend_obj_fun = csvread(filename,201,0,[201,0,300, 0]);
Heur_cost = csvread(filename,201,3,[201,3,300, 3]);
AMPL_cost = csvread(filename,201,7,[201,7,300, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
m_100_10=mean(Heur_cost)

% It: 500/10
Wend_obj_fun = csvread(filename,301,0,[301,0,400, 0]);
Heur_cost = csvread(filename,301,3,[301,3,400, 3]);
AMPL_cost = csvread(filename,301,7,[301,7,400, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
m_500_10=mean(Heur_cost)

% It: 500/5
Wend_obj_fun = csvread(filename,401,0,[401,0,500, 0]);
Heur_cost = csvread(filename,401,3,[401,3,500, 3]);
AMPL_cost = csvread(filename,401,7,[401,7,500, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
m_500_5=mean(Heur_cost)

% It: 500/15
Wend_obj_fun = csvread(filename,501,0,[501,0,600, 0]);
Heur_cost = csvread(filename,501,3,[501,3,600, 3]);
AMPL_cost = csvread(filename,501,7,[501,7,600, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
m_500_15=mean(Heur_cost)

% It: 500/20
Wend_obj_fun = csvread(filename,601,0,[601,0,700, 0]);
Heur_cost = csvread(filename,601,3,[601,3,700, 3]);
AMPL_cost = csvread(filename,601,7,[601,7,700, 7]);

Obj_AMPL = [Wend_obj_fun, AMPL_cost];
R_O_A = corrcoef(Obj_AMPL)
m_500_20=mean(Heur_cost)