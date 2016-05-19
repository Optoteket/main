res <- read.csv("obj_func_val.csv", header=TRUE, sep=",")
x <- res[,1]
y1 <- res[,2]
y2 <- res[,3]
#par("usr")
#plot.window(xlim=range(x),ylim=range(y1))
#plot(x, y1, xlab = "Iterations", ylab="Obj function val",type="l", main="Weekend objective function values",axes=FALSE)
#plot(x, y1, type="l", main="Weekend objective function values",axes=FALSE, xlab="", ylab="")
#plot.new()

#par(new=TRUE)
#plot(x, y2, type="l",axes=FALSE, xlab="", ylab="", col="red")
#par(new=TRUE)
#lines(x, y2, col ="red")
#par(new=TRUE)
#plot(res[,1], res[,4], type="l", col ="green")
#par(new=TRUE)
#plot(res[,1], res[,5], type="l", col ="blue")

#axis(1); axis(2); box()
#plot.window(xlim=range(x),ylim=range(y2))
#par(xaxs="i",yaxs="i")
#lines(x,y2)
#axis(1); axis(2); box()

#axis(1, at=seq(0,length(res[,1])+100,50),labels=seq(0,length(res[,1])+100,50), las=0)
#axis(2, at=seq(0,length(res[,2]),5),labels=seq(0,length(res[,2]),5), las=2)
#title("Objective function plots", xlab="X values",ylab="Y=X"	)

par(mar = c(5,5,2,5))
plot(x, y1, type="l", col="red3", 
             ylab=expression(-log[10](italic(p))),
             ylim=c(min(res[,2])-1,max(res[,2])+1))

plot(x, y2, type="l", axes=F, xlab=NA, ylab=NA)
legend("topleft",
       legend=c(expression(-log[10](italic(p))), "N genes"),
       lty=c(1,0), pch=c(NA, 16), col=c("red3", "black"))
