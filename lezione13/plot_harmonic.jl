using DataFrames
using CSV
using Plots
#%%
data_v = open("harmonic_verlet.dat")
data_rk = open("harmonic_rk.dat")

df_v=CSV.read(data_v, header=false, delim=" ")
df_rk=CSV.read(data_rk, header=false, delim=" ")
t_v=df_v[1]
x_v=df_v[2]
v_v=df_v[3]

t_rk=df_rk[1]
x_rk=df_rk[2]
v_rk=df_rk[3]
#%%
# plot(t_v, x_v, label="x velocity_Verlet", dpi=600)
# plot!(t_v, v_v, label="v velocity_Verlet", dpi=600)
# xaxis!(:log10)
# yaxis!(:log10)
#%%
K_v=1//2*v_v.^2
U_v=1//2*x_v.^2
En_v=K_v+U_v

K_rk=1//2*v_rk.^2
U_rk=1//2*x_rk.^2
En_rk=K_rk+U_rk
print(En_rk)
plot(t_v, En_v, label="Energy Verlet", dpi=600)
plot!(t_rk, En_rk, label="Energy Runge-Kutta", dpi=600)
plot!(legend=:topleft)
xlabel!("step")
ylabel!("Energy")
savefig("harmonic.png")
