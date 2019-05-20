using DataFrames
using CSV
using Plots
#%%
data_1 = open("ode05.dat")
data_2 = open("ode025.dat")
data_3 = open("ode01.dat")
data_4 = open("ode001.dat")

df1=CSV.read(data_1, header=false, delim=" ")
df2=CSV.read(data_2, header=false, delim=" ")
df3=CSV.read(data_3, header=false, delim=" ")
df4=CSV.read(data_4, header=false, delim=" ")

plot(df1[1],df1[2], label="h=0.5")
plot!(df2[1],df2[2], label="h=0.25")
plot!(df3[1],df3[2], label="h=0.01")
plot!(df4[1],df4[2], label="h=0.001")
# xaxis!(:log10)
# yaxis!(:log10)
