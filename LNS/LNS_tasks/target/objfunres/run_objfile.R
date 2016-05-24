res <- read.csv("obj_func_vals_.csv", header=TRUE, sep=",")
#res <- read.csv("obj_func_vals_2016_5_18 23:20:28.csv", header=TRUE, sep=",")
x <- res[,1]
y1 <- res[,2]
y2 <- res[,3]
y3 <- res[,4]
y4 <- res[,5]
#Stand in lib and ass
y5 <- res[,6]
y6 <- res[,7]

#par(mfrow=c(2,1))

g_range <- range(y5,y6)

plot(y1, type="l", col="blue", ylim=g_range, axes=FALSE, ann=FALSE)
axis(1, at=seq(0,length(x)+100,50))
box()
axis(2, las=1, lty=2, at=seq(g_range[1],g_range[2]+5))

#Lines
lines(y5, lty=1, col="red")
lines(y6, lty=1, col="green")
#lines(y4, lty=1, col="purple")
#lines(y3, lty=1, col="green")
#lines(y4, lty=1, col="purple")

legend(-30, g_range[2], c("Obj fun","Stand ins","Shift avail","Day avail"), cex=0.5, col=c("blue","red","green","purple"), pch=21:22, lty=1:2);
#legend(1, 8, c("Stand ins","Shift avail","Day avail"), cex=0.5, col=c("blue","green","purple"), pch=21:22, lty=1:2);

title("Feasible solution: 3,0", xlab="Iteration number",ylab="Objective fun val")

########################
#res <- read.csv("obj_func_vals_1_10_10_infeas_0.csv", header=TRUE, sep=",")
#res <- read.csv("obj_func_vals_0_0_0_infeas_4.csv", header=TRUE, sep=",")
x <- res[,1]
y1 <- res[,2]
y2 <- res[,3]
y3 <- res[,4]
y4 <- res[,5]

g_range <- range(y1, y2, y3, y4)

#plot(y1, type="l", col="blue", ylim=g_range, axes=FALSE, ann=FALSE)
#axis(1, at=seq(0,length(x)+100,50))
#box()
#axis(2, las=1, lty=2, at=g_range[1]:g_range[2])

#Lines
#lines(y2, lty=1, col="red")
#lines(y3, lty=1, col="green")
#lines(y4, lty=1, col="purple")
#lines(y3, lty=1, col="green")
#lines(y4, lty=1, col="purple")

#legend(1, 8, c("Obj fun","Stand ins","Shift avail","Day avail"), cex=0.5, col=c("blue","red","green","purple"), pch=21:22, lty=1:2);
#legend(1, 8, c("Stand ins","Shift avail","Day avail"), cex=0.5, col=c("blue","green","purple"), pch=21:22, lty=1:2);

#title("Infeasible solution", xlab="Iteration number",ylab="Objective fun val")


#####################################################################################################################


#plot(x, y1, xlab = "Iterations", ylab="Obj function val",type="l", main="Weekend objective function values")








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

#par(mar = c(5,5,2,5))
#plot(x, y1, type="l", col="red3",    ylab=expression(-log[10](italic(p))), ylim=c(min(res[,2])-1,max(res[,2])+1))

#plot(x, y2, type="l", axes=F, xlab=NA, ylab=NA)
#legend("topleft",legend=c(expression(-log[10](italic(p))), "N genes"),  lty=c(1,0), pch=c(NA, 16), col=c("red3", "black"))
