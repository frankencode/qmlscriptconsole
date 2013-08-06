import com.nokia.ScriptConsole 1.0

ScriptEditor {
    onSubmitted: {
        var result = ""
        try {
            result = eval(text)
        }
        catch (any) {
            result = any
        }
        if (result !== undefined)
            log(result.toString())
    }
    function log() {
        var sl = []
        for (var i = 0; i < arguments.length; ++i)
            sl.push(String(arguments[i]))
        logList(sl)
    }
}
