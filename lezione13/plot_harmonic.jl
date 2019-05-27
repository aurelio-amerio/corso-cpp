using DataFrames
using CSV
using Plots
#%%
run(`./harmonic`)
data_v = open("harmonic_verlet.dat")
data_v4 = open("harmonic_verlet4.dat")
data_rk = open("harmonic_rk.dat")
data_rk4 = open("harmonic_rk4.dat")

df_v=CSV.read(data_v, header=false, delim=" ")
df_v4=CSV.read(data_v4, header=false, delim=" ")
df_rk=CSV.read(data_rk, header=false, delim=" ")
df_rk4=CSV.read(data_rk4, header=false, delim=" ")

t_v=df_v[1]
x_v=df_v[2]
v_v=df_v[3]

t_v4=df_v4[1]
x_v4=df_v4[2]
v_v4=df_v4[3]

t_rk=df_rk[1]
x_rk=df_rk[2]
v_rk=df_rk[3]

t_rk4=df_rk4[1]
x_rk4=df_rk4[2]
v_rk4=df_rk4[3]
#%%

K_v=1//2*v_v.^2
U_v=1//2*x_v.^2
En_v=K_v+U_v

K_v4=1//2*v_v4.^2
U_v4=1//2*x_v4.^2
En_v4=K_v4+U_v4

K_rk=1//2*v_rk.^2
U_rk=1//2*x_rk.^2
En_rk=K_rk+U_rk

K_rk4=1//2*v_rk4.^2
U_rk4=1//2*x_rk4.^2
En_rk4=K_rk4+U_rk4
#%%
plot(t_v, En_v, label="Energy Verlet", dpi=600)
plot!(t_v4, En_v4, label="Energy Verlet 4", dpi=600)
plot!(t_rk, En_rk, label="Energy Runge-Kutta", dpi=600)
plot!(t_rk4, En_rk4, label="Energy Runge-Kutta 4", dpi=600, line=:dash, color="black")
plot!(legend=:topleft)
xlabel!("step")
ylabel!("Energy")
savefig("harmonic4.png")

#%%
plot(t_v4, En_v4, label="Energy Verlet 4", dpi=600)
plot!(t_rk4, En_rk4, label="Energy Runge-Kutta 4", dpi=600, line=:dash)
plot!(legend=:bottomleft)
xlabel!("step")
ylabel!("Energy")
savefig("harmonic2.png")


pi/4
