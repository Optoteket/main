out = zeros(10,10);
for v=1:10
    for w = 1:10
        out(v,w) = mod(w-v+10,10)+1;
    end
end
out