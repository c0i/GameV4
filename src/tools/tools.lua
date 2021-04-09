
local tools = {}

function tools.getAddr(obj)
    local addrStr = string.gsub(tostring(obj), "table: ", "")
    local addrNumb = tonumber(addrStr)
    return addrNumb
end

return tools