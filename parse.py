with open("logoutput.txt", "r") as file:
    with open("processed.txt","w") as processed:
        for line in file:
            currentline = line.split(",")
            if int(currentline[1]) == 1:
                processed.write("[CIRCBUF]:")
            if int(currentline[1]) == 2:
                processed.write("[CONVERSION]:")
            if int(currentline[1]) == 3:
                processed.write("[DATA]:")
            if int(currentline[1]) == 4:
                processed.write("[DEBUG]:")
            if int(currentline[1]) == 5:
                processed.write("[GPIO]:")
            if int(currentline[1]) == 6:
                processed.write("[LOGGER_QUEUE]:")
            if int(currentline[1]) == 7:
                processed.write("[LOGGER]:")
            if int(currentline[1]) == 8:
                processed.write("[MAIN]:")
            if int(currentline[1]) == 9:
                processed.write("[MEMORY]:")
            if int(currentline[1]) == 10:
                processed.write("[NORDIC]:")
            if int(currentline[1]) == 11:
                processed.write("[PROJECT1]:")
            if int(currentline[1]) == 12:
                processed.write("[PROJECT2]:")
            if int(currentline[1]) == 13:
                processed.write("[PROJECT3]:")
            if int(currentline[1]) == 14:
                processed.write("[PROJECT4]:")
            if int(currentline[1]) == 15:
                processed.write("[SPI]:")
            if int(currentline[1]) == 16:
                processed.write("[TEST]:")
            if int(currentline[1]) == 17:
                processed.write("[UART]:")
            processed.write(" ")
            processed.write(currentline[2])
            processed.write(" - ")
            if int(currentline[0]) == 1:
                processed.write("SYSTEM_ID")
            if int(currentline[0]) == 2:
                processed.write("SYSTEM_VERSION")
            if int(currentline[0]) == 3:
                processed.write("LOGGER_INITIALIZED")
            if int(currentline[0]) == 4:
                processed.write("GPIO_INITIALIZED")
            if int(currentline[0]) == 5:
                processed.write("SYSTEM_INITIALIZED")
            if int(currentline[0]) == 6:
                processed.write("SYSTEM_HALTED")
            if int(currentline[0]) == 7:
                processed.write("INFO")
            if int(currentline[0]) == 8:
                processed.write("WARNING")
            if int(currentline[0]) == 9:
                processed.write("ERROR")
            if int(currentline[0]) == 10:
                processed.write("PROFILING_STARTED")
            if int(currentline[0]) == 11:
                processed.write("PROFILING_RESULT")
            if int(currentline[0]) == 12:
                processed.write("PROFILING_COMPLETED")
            if int(currentline[0]) == 13:
                processed.write("DATA_RECEIVED")
            if int(currentline[0]) == 14:
                processed.write("DATA_ANALYSIS_STARTED")
            if int(currentline[0]) == 15:
                processed.write("DATA_ALPHA_COUNT")
            if int(currentline[0]) == 16:
                processed.write("DATA_NUMERIC_COUNT")
            if int(currentline[0]) == 17:
                processed.write("DATA_PUNCTUATION_COUNT")
            if int(currentline[0]) == 18:
                processed.write("DATA_MISC_COUNT")
            if int(currentline[0]) == 19:
                processed.write("DATA_ANALYSIS_COMPLETED")
            if int(currentline[0]) == 20:
                processed.write("HEARTBEAT")
            if int(currentline[0]) == 21:
                processed.write("CORE_DUMP")

            if currentline[3]:
                processed.write(" - ")
                array = currentline[3].split(".")
                for s in array:
                    processed.write(s)
                    processed.write(' ')
                if int(currentline[0])^int(currentline[1])^int(currentline[2])^len(array) != int(currentline[4]):
                    processed.write("TRANSMISSION ERROR")
            else:
                if int(currentline[0])^int(currentline[1])^int(currentline[2]) != int(currentline[4]):
                    processed.write("TRANSMISSION ERROR")
            processed.write("\n")
