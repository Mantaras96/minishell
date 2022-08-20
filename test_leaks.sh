#!/bin/bash

ps | grep minishell | head -n 2 | awk '{system ("leaks " $1)}'