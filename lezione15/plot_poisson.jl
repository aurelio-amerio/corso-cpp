using DataFrames
using CSV
using Plots
#%%
data_s0 = open("poisson_s0.dat")
df_s0=CSV.read(data_s0, header=false, delim=" ")
r_s0=df_s0[1]
phi_s0=df_s0[2]

data_s02 = open("poisson_s02.dat")
df_s02=CSV.read(data_s02, header=false, delim=" ")
r_s02=df_s02[1]
phi_s02=df_s02[2]

data_s04 = open("poisson_s04.dat")
df_s04=CSV.read(data_s04, header=false, delim=" ")
r_s04=df_s04[1]
phi_s04=df_s04[2]

data_s06 = open("poisson_s06.dat")
df_s06=CSV.read(data_s06, header=false, delim=" ")
r_s06=df_s06[1]
phi_s06=df_s06[2]

data_s08 = open("poisson_s08.dat")
df_s08=CSV.read(data_s08, header=false, delim=" ")
r_s08=df_s08[1]
phi_s08=df_s08[2]

data_s1 = open("poisson_s1.dat")
df_s1=CSV.read(data_s1, header=false, delim=" ")
r_s1=df_s1[1]
phi_s1=df_s1[2]

#%%
plot(df_s0[1], df_s0[2], label="s 0.0", dpi=600)
plot!(df_s02[1], df_s02[2], label="s 0.2", dpi=600)
plot!(df_s04[1], df_s04[2], label="s 0.4", dpi=600)
plot!(df_s06[1], df_s06[2], label="s 0.6", dpi=600)
plot!(df_s08[1], df_s08[2], label="s 0.8", dpi=600)
plot!(df_s1[1], df_s1[2], label="s 1.0", dpi=600)

plot!(grid=true, legend=:topleft)
xlabel!("steps")
ylabel!("phi")
savefig("poisson_vari_s.png")
# xaxis!(:log10)
# yaxis!(:log10)
