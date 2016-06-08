# Read values from text file. objfcn, feasible, standins and maxmin
plot_data <- read.table("./target/Saved results/Plots for Report/1Phase1iterNoRerun/feasible.txt", header=T) #Change this path!

#Compute max y-values
max_y_feasible <- max(plot_data$feasible)



#Define colors to be used
plot_colors <- c("blue")

# Start PNG device driver to save output to figure.png
png(filename="./target/Saved results/Plots for Report/1Phase1iterNoRerun/Rfeasible.png", height=1000, width=1000, bg="white")
#jpeg('rplot.jpg')

#plot each of the columns
plot(plot_data$feasible, col = plot_colors[1])
#Make x-axis
#axis(1, at=1:5, lab=c("Mon", "Tue", "Wed", "Thu", "Fri"))
#Make y-axis
#axis(2, las=1, at=4*0:max_y_objfcn)


# Turn off device driver (to flush output to png)
dev.off()



