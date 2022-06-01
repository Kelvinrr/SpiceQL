import json
import pyspiceql

def lambda_handler(event, context):
    
    # TODO implement
    print(f"event: ", event)
    print(f"context: ", context)
    print(dir(pyspiceql))
    
    try: 
        func = getattr(pyspiceql, event["func"])
        event.pop('func')
        ret = func(**event)
        
        return {
            "statusCode" : 200,
            "body" : json.dumps({
                "return" : ret
            })
        }
        
    except Exception as e: 
        return {
            "statusCode" : 500,
            "body" : json.dumps({
                "error" : str(e)
            })
        }

