import pytest

async def test_positive(service_client):
    response = await service_client.post("/announce", params= { "info_hash": "00000000000000000000",
                                                                "peer_id": "GYTORR-0000000000000",
                                                                "ip": "1.1.1.1",
                                                                "port": "6889",
                                                                "uploaded": "0",
                                                                "downloaded": "0",
                                                                "left": "0",
                                                                "event": "started"})
    assert response.status == 200
    assert response.text == "Hello, GYTORR-0000000000000\n"


async def test_incorrect(service_client):
    response = await service_client.post("/announce", params={"name": "Tester"})
    assert response.status == 400
    assert response.text == ""

