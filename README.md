# Producer_Consumers-problem

Producer_Consumers problem

Producer = Feeder
Consumers = Readers


HOW TO RUN:
  Type in your terminal   "make"    to compile
  Then to execute type    "./main x y"  where x are the processes(1 producer, x-1 consumer) and y are the loops for feeder to write and readers to read
  To try again you must type "make clean" and all over again


WHAT IT DOES:
  Feeder(Producer) writes to the shared memory an integer and the time.   
  Readers(consumers) read that integer and the time of feeder, and they write to a file(different for every reader), the time they took them to read.
  Also, readers print the average time.


SYNCHRONIZATION:
  I use four semaphores(counting and not counting) for synchronization of processes with shared memory and themselves.
  FS:  for access to Feeder
  CS:  for access to Consumer(reader)
  CTR: for counting readers
  TS:  necessary blocking

HOW IT WORKS:
  Feeder goes down, writes to the memory and does up the CS for consumers to start reading. After that it blocks at CTR.
  Consumer one at a time reads, and does up CTR, and blocks at TS. After all read the message, CTR unlocks feeder. Feeder unlocks readers by doing up by x the TS and blocks and blocks at FS. Readers do up the FS and blocked at CS. Feeder goes down...  
  The above is happening y times.


  RESULTS FOR SOME TRY'S:

  N=10, M=100   I am 2717 and my running average is: 0.010000
          I am 2715 and my running average is: 0.010000
          I am 2714 and my running average is: 0.010000
          I am 2713 and my running average is: 0.010000
          I am 2719 and my running average is: 0.010000
          I am 2718 and my running average is: 0.010000
          I am 2721 and my running average is: 0.010000
          I am 2720 and my running average is: 0.010000
          I am 2722 and my running average is: 0.010000
          I am 2716 and my running average is: 0.010000

  N=10, M=1000  I am 2740 and my running average is: 0.013000
          I am 2736 and my running average is: 0.013000
          I am 2739 and my running average is: 0.011000
          I am 2735 and my running average is: 0.013000
          I am 2734 and my running average is: 0.012000
          I am 2743 and my running average is: 0.017000
          I am 2738 and my running average is: 0.014000
          I am 2737 and my running average is: 0.015000
          I am 2741 and my running average is: 0.016000
          I am 2742 and my running average is: 0.015000

  N=67, M=10000  I am 2917 and my running average is: 0.044300
          I am 2924 and my running average is: 0.040800
          I am 2914 and my running average is: 0.047900
          I am 2947 and my running average is: 0.042700
          I am 2960 and my running average is: 0.043700
          I am 2913 and my running average is: 0.046000
          I am 2969 and my running average is: 0.045300
          I am 2919 and my running average is: 0.043600
          I am 2928 and my running average is: 0.050800
          I am 2942 and my running average is: 0.047300
          I am 2941 and my running average is: 0.042800
          I am 2905 and my running average is: 0.044900
          I am 2958 and my running average is: 0.042700
          I am 2944 and my running average is: 0.045500
          I am 2911 and my running average is: 0.050800
          I am 2945 and my running average is: 0.049700
          I am 2952 and my running average is: 0.045000
          I am 2916 and my running average is: 0.045400
          I am 2939 and my running average is: 0.045600
          I am 2940 and my running average is: 0.045200
          I am 2930 and my running average is: 0.048200
          I am 2938 and my running average is: 0.043600
          I am 2953 and my running average is: 0.043100
          I am 2964 and my running average is: 0.043100
          I am 2923 and my running average is: 0.042200
          I am 2962 and my running average is: 0.047900
          I am 2910 and my running average is: 0.046500
          I am 2912 and my running average is: 0.043000
          I am 2918 and my running average is: 0.041400
          I am 2920 and my running average is: 0.048600
          I am 2943 and my running average is: 0.045500
          I am 2936 and my running average is: 0.046500
          I am 2931 and my running average is: 0.046000
          I am 2955 and my running average is: 0.046400
          I am 2937 and my running average is: 0.046800
          I am 2906 and my running average is: 0.046300
          I am 2963 and my running average is: 0.044000
          I am 2950 and my running average is: 0.045800
          I am 2933 and my running average is: 0.044200
          I am 2959 and my running average is: 0.044000
          I am 2965 and my running average is: 0.041900
          I am 2956 and my running average is: 0.044400
          I am 2925 and my running average is: 0.049600
          I am 2932 and my running average is: 0.043900
          I am 2915 and my running average is: 0.042800
          I am 2961 and my running average is: 0.043100
          I am 2954 and my running average is: 0.047800
          I am 2934 and my running average is: 0.047100
          I am 2957 and my running average is: 0.042800
          I am 2949 and my running average is: 0.045900
          I am 2926 and my running average is: 0.043900
          I am 2908 and my running average is: 0.045300
          I am 2970 and my running average is: 0.042900
          I am 2909 and my running average is: 0.043400
          I am 2921 and my running average is: 0.044700
          I am 2948 and my running average is: 0.045300
          I am 2927 and my running average is: 0.048300
          I am 2904 and my running average is: 0.040700
          I am 2907 and my running average is: 0.044300
          I am 2968 and my running average is: 0.041500
          I am 2967 and my running average is: 0.047300
          I am 2929 and my running average is: 0.042900
          I am 2935 and my running average is: 0.043800
          I am 2922 and my running average is: 0.048400
          I am 2951 and my running average is: 0.044800
          I am 2966 and my running average is: 0.054200
          I am 2946 and my running average is: 0.046600   
