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
plot(df_rk[1],df_rk[2], label="Runge-Kutta", dpi=600)
plot!(df_rk4[1],df_rk4[2], label="RK 4th order", dpi=600)
plot!(df_eu[1],df_eu[2], label="Euler", dpi=600)

xaxis!(:log10, xlims=(1e-12,Inf))
yaxis!(:log10, ylims=(1e-12,Inf))
