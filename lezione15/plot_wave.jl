using DataFrames
using CSV
using Plots
#%%
data_s0 = open("wave1.dat")
df_s0=CSV.read(data_s0, header=false, delim=" ")
r_s0=df_s0[1]
phi_s0=df_s0[2]


#%%
plot(df_s0[1], df_s0[2], label="k 1", dpi=600)
# plot!(df_s02[1], df_s02[2], label="s 0.2", dpi=600)
# plot!(df_s04[1], df_s04[2], label="s 0.4", dpi=600)
# plot!(df_s06[1], df_s06[2], label="s 0.6", dpi=600)
# plot!(df_s08[1], df_s08[2], label="s 0.8", dpi=600)
# plot!(df_s1[1], df_s1[2], label="s 1.0", dpi=600)

plot!(grid=true, legend=:topleft)
xlabel!("steps")
ylabel!("phi")
# savefig("poisson_vari_s.png")
# xaxis!(:log10)
# yaxis!(:log10)
