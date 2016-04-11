out = zeros(10,10);
for v=1:10
    for w = 1:10
        out(v,w) = mod(w-v+10,10)+1;
    end
end
out

num_weeks = 5;
num_rotations = 4;
out = zeros(num_weeks,num_rotations);
for v=1:num_rotations
    for w = 1:num_weeks
        out(v,w) = mod(w-v+num_weeks,num_weeks)+1;
    end
end
out
