res <- read.csv("obj_func_val.csv", header=TRUE, sep=",")
par(mfrow=c(1,1))
plot(res[,1], res[,2], xlab = "Iterations", ylab="Obj function val",type="l", main="Weekend objective function values", axes=F)
axis(1, at=seq(0,length(res[,1])+100,50),labels=seq(0,length(res[,1])+100,50), las=0)
axis(2, at=seq(0,length(res[,2]),5),labels=seq(0,length(res[,2]),5), las=2)

