using DataFrames
using CSV
using Plots
#%%
data_v = open("pendulum.dat")
df_v=CSV.read(data_v, header=false, delim=" ")
t_v=df_v[1]
theta_v=df_v[2]
omega_v=df_v[3]

data_rk = open("pendulum_rk.dat")
df_rk=CSV.read(data_rk, header=false, delim=" ")
t_rk=df_rk[1]
theta_rk=df_rk[2]
omega_rk=df_rk[3]
#%%
plot(df_v[1], df_v[2], label="theta", dpi=600)
plot(df_rk[1], df_rk[2], label="theta", dpi=600)
# xaxis!(:log10)
# yaxis!(:log10)
#%%
E_v = (omega_v.^2)/2 + (ones(length(omega_v))-cos.(theta_v))
E_rk = (omega_rk.^2)/2 + (ones(length(omega_rk))-cos.(theta_rk))

plot(t_v, E_v, label="Verlet", dpi=600)
plot!(t_rk, E_rk, label="RK2", dpi=600)
plot!(legend=:topleft)
# ylims!(0,0.4)
ylabel!("E/(m L^2)")
xlabel!("step")
savefig("pendulum.png")
