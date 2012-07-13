library(RHmm)

data(weather)
ResWeather <- HMMFit(weather, dis="DISCRETE", nStates=3)

v <- c("foo","bar","foobar")
fb <- forwardBackward(ResWeather, v, logData=FALSE)
print(fb)

VitFit <- viterbi(ResWeather,v)
print(VitFit)

