analysis-omega/macros
=====================

## Requirements

To load all required functions, you must include the dir `${PRODIR}/macros/include` into your `ROOT_INCLUDE_PATH` environment variable.

## Order of execution

1. First batch.

```
./send_long_macros.sh --kind data --stage test;
./send_long_macros.sh --kind data --stage ana --part eta;
./send_long_macros.sh --kind data --stage ana --part omega;
./send_long_macros.sh --kind sim --stage ana --part eta;
./send_long_macros.sh --kind sim --stage ana --part omega;
./send_long_macros.sh --stage radcorr --part eta;
./send_long_macros.sh --stage radcorr --part omega;
```

2. Second batch - Send after all the previous jobs have finished.

```
./send_long_macros.sh --kind data --stage ana-fix --part omega;
./send_long_macros.sh --stage radcorr-fix --part omega;
```

3. Third batch - Execute after all the previous jobs have finished.

```
./exec_short_macros.sh --kind data --stage ana --part eta;
./exec_short_macros.sh --kind data --stage ana --part omega;
./exec_short_macros.sh --kind sim --stage ana --part eta;
./exec_short_macros.sh --kind sim --stage ana --part omega;
./exec_short_macros.sh --stage pre-radcorr --part eta;
./exec_short_macros.sh --stage pre-radcorr --part omega;
```

4. Last batch - Execute after obtaining Radiative Corrections.

```
./exec_short_macros.sh --stage radcorr --part eta;
./exec_short_macros.sh --stage radcorr --part omega;
```
