using DataFrames
using CSV
using Plots
#%%
data_rk = open("rk_error.dat")
data_rk4 = open("rk4_error.dat")
data_eu = open("eu_error.dat")


df_rk=CSV.read(data_rk, header=false, delim=" ")
df_rk4=CSV.read(data_rk4, header=false, delim=" ")
df_eu=CSV.read(data_eu, header=false, delim=" ")
#%%
x_=4:2048
eu=x_.^-1
rk=x_.^-2
rk4=x_.^-4
#%%
plot(df_rk[1],df_rk[2], label="Runge-Kutta", color="black", dpi=600)
plot!(x_,rk, label="y=x^-2", color="black", line=(:dash))

plot!(df_rk4[1],df_rk4[2], label="RK 4th order", color="red")
plot!(x_,rk4, label="y=x^-4", color="red" , line=(:dash))

plot!(df_eu[1],df_eu[2], label="Euler", color="blue")
plot!(x_,eu, label="y=x^-1",color="blue", line=(:dash))





xaxis!(:log10, xlims=(4,2048))
yaxis!(:log10, ylims=(1e-15,Inf))
title!("error as a function of n_steps")
xlabel!("n_steps")
ylabel!("error")
plot!(legend=:bottom)
savefig("errors.png")
