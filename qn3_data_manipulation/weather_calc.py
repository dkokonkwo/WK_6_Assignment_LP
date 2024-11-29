import dataman

print("Mode Average Temperature:")
print(dataman.mode("weather.csv"))
print("Median Average Temperature:")
print(dataman.median("weather.csv"))
print("Standard Deviation:")
print("%.2f" % dataman.standev("weather.csv"))
