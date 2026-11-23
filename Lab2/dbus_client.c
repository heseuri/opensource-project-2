
#include <stdio.h>
#include <string.h>
#include <gio/gio.h>

int main()
{
    GDBusConnection *conn;
    GVariant *result;
    GError *error = NULL;
    char msg[200];
    const char *reply;

    conn = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);

    if (conn == NULL) {
        printf("D-Bus 연결 실패: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    printf("보낼 알림 메시지: ");
    if (fgets(msg, sizeof(msg), stdin) == NULL) {
        g_object_unref(conn);
        return 1;
    }

    msg[strcspn(msg, "\n")] = '\0';

    result = g_dbus_connection_call_sync(
        conn,
        "com.example.NotifyService",
        "/com/example/Notify",
        "com.example.Notify",
        "SendNotification",
        g_variant_new("(s)", msg),
        G_VARIANT_TYPE("(s)"),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        &error);

    if (result == NULL) {
        printf("메시지 전송 실패: %s\n", error->message);
        g_clear_error(&error);
    }
    else {
        g_variant_get(result, "(&s)", &reply);
        printf("서버 응답: %s\n", reply);
        g_variant_unref(result);
    }

    g_object_unref(conn);

    return 0;
}

